#!/bin/bash
set -o posix

function attention_echo {
	echo -e "\n******************************************"
	echo -e "*\t$1 *"
	echo -e "******************************************\n"
}

# Default project name (no spaces)
NAME_PROJECT="Dauphine"
# If there is a T_NAME_PROJECT, assign it to NAME_PROJECT
if [ ! -z $T_NAME_PROJECT ]
then
	NAME_PROJECT=${T_NAME_PROJECT}
else
	attention_echo "No T_NAME_PROJECT set"
fi

# Target names
TARGET_PROJECT=${NAME_PROJECT}_exec
TARGET_GTEST=${NAME_PROJECT}_GTest

# Doxygen files directory name
DIRNAME_DOXYGEN=html

# Some directories
DIR_PROJECT_ROOT=$(dirname "$(readlink -f $0)")
DIR_PROJECT_ROOT=$(echo "$DIR_PROJECT_ROOT" | sed 's/\/utils\/local//g')
DIR_BUILD=${DIR_PROJECT_ROOT}/build
DIR_SRC=${DIR_PROJECT_ROOT}/src
DIR_BUILD_SRC=${DIR_BUILD}/src
DIR_BUILD_TEST=${DIR_BUILD}/test
DIR_REPORTS=${DIR_BUILD}/reports
DIR_REPORTS_CPPLINT=${DIR_REPORTS}/cpplint-reports
DIR_REPORTS_CPPCHECK=${DIR_REPORTS}/cppcheck-reports
DIR_REPORTS_GCOVR=${DIR_REPORTS}/gcovr-reports
DIR_GCOVR_FILES=${DIR_BUILD_SRC}/CMakeFiles
DIR_GCOVR_FILES_TEST=${DIR_BUILD_TEST}/CMakeFiles
DIR_UTILS=${DIR_PROJECT_ROOT}/utils
DIR_DOXYGEN=${DIR_BUILD}/${DIRNAME_DOXYGEN}
DIR_TMP_GHPAGES=${DIR_PROJECT_ROOT}/push_to_ghpages

# CPack packaged project
FILES_CPACK=${DIR_BUILD}/${NAME_PROJECT}*.zip

function success_exit {
	attention_echo "Finished build script"
	exit 0
}

function do_cppcheck {
	attention_echo "cppcheck"

	mkdir -p ${DIR_REPORTS_CPPCHECK} || exit $?

	# Generate cppcheck xml
	cppcheck -v --enable=all ${DIR_SRC} -I${DIR_SRC} --xml-version=2 2> cppcheck-only-result.xml

	# Generate html from it
	${DIR_UTILS}/cppcheck-htmlreport.py\
		--file=cppcheck-only-result.xml\
		--report-dir=${DIR_REPORTS_CPPCHECK}\
		--source-dir=${DIR_PROJECT_ROOT}\
		--title=${NAME_PROJECT}
}

function do_cpplint {
	attention_echo "cpplint.py"

	mkdir -p ${DIR_REPORTS_CPPLINT} || exit $?

	# Generate cppcheck-style xml from cpplint output
	${DIR_UTILS}/cpplint.py --linelength=95 --extensions=h,cpp --verbose=0\
		--filter=-whitespace/blank_line,-whitespace/tab,-whitespace/comments,-whitespace/newline,-whitespace/braces,-legal,-readability/braces,-readability/multiline_comment,-build/header_guard\
		${DIR_SRC}/*.* 2>&1|\
		sed 's/"/\&quot;/g' >&1| sed 's/</\&lt;/g' >&1| sed 's/>/\&gt;/g' >&1|\
		sed "s/'/\&apos;/g" >&1| sed 's/\&/\&amp;/g' >&1|\
		${DIR_UTILS}/cpplint_to_cppcheckxml.py &> cpplint-cppcheck-result.xml

	# Generate html from it
	${DIR_UTILS}/cppcheck-htmlreport.py\
		--file=cpplint-cppcheck-result.xml\
		--report-dir=${DIR_REPORTS_CPPLINT}\
		--source-dir=${DIR_PROJECT_ROOT}\
		--title=${NAME_PROJECT}

	# Change Cppcheck things to cpplint
	sed -i 's/Cppcheck/cpplint/g' ${DIR_REPORTS_CPPLINT}/index.html
	sed -i 's/a\ tool\ for\ static\ C\/C++\ code\ analysis/an\ open\ source\ lint\-like\ tool\ from\ Google/g' ${DIR_REPORTS_CPPLINT}/index.html
	sed -i 's/http:\/\/cppcheck.sourceforge.net/http:\/\/google\-styleguide.googlecode.com\/svn\/trunk\/cpplint\/cpplint.py/g' ${DIR_REPORTS_CPPLINT}/index.html
	sed -i 's/IRC: <a href=\"irc:\/\/irc.freenode.net\/cppcheck\">irc:\/\/irc.freenode.net\/cppcheck<\/a>/\ /g' ${DIR_REPORTS_CPPLINT}/index.html
}

function do_valgrind {
	attention_echo "Valgrind"

	# Valgrind report
	SDL_AUDIODRIVER=dummy SDL_VIDEODRIVER=dummy valgrind\
		--xml=yes --xml-file=${DIR_REPORTS}/valgrind-exec-report.xml\
		--leak-check=full\
		--track-origins=yes\
		${DIR_PROJECT_ROOT}/${TARGET_PROJECT}

	# Test report
	${DIR_BUILD_TEST}/${TARGET_GTEST} --gtest_output=xml:${DIR_REPORTS}/gtest-report.xml
}

function do_gcovr {
	attention_echo "gcovr"

	mkdir -p ${DIR_REPORTS_GCOVR} || exit $?

	gcovr --verbose\
		--root=${DIR_GCOVR_FILES_TEST}\
		--filter=${DIR_SRC}/\
		--html --html-details --output=${DIR_REPORTS_GCOVR}/index.html
}

function code_analysis {
	do_cppcheck
	do_cpplint
	do_valgrind
	do_gcovr
}

#########################################
################ "Main" #################
#########################################

attention_echo "after_success : ${NAME_PROJECT}"

# If there is no build directory, exit
if [ ! -d "$DIR_BUILD" ]
then
	attention_echo "No build directory! Exiting..."
	exit 3
fi

pushd ${DIR_BUILD}

code_analysis

popd
