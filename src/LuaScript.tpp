#include "Logger.h"

// LuaScript::unlua_get

template<typename T>
T LuaScript::unlua_get(const std::string& variableName_) {
    if(!luaState) {
        Log(ERROR) << "Script is not loaded! [" << variableName_ << "]";
        return unlua_getDefault<T>();
    }

    T result;
    if(unlua_getToStack(variableName_)) { // variable succesfully on top of stack
        result = unlua_getValue<T>(variableName_);  
    }
    else {
        result = unlua_getDefault<T>();
    }

    unlua_clean();
    return result;
}

// LuaScript::unlua_getDefault

template<typename T>
T LuaScript::unlua_getDefault() {
	return 0;
}

template<>
inline std::string LuaScript::unlua_getDefault<std::string>() {
	return "null";
}


// LuaScript::unlua_getValue

template<typename T>
T LuaScript::unlua_getValue(const std::string& variableName_) {
    return 0;
}

template <> 
inline bool LuaScript::unlua_getValue<bool>(const std::string& variableName_) {
	((void)(variableName_));
	return (bool)lua_toboolean(luaState, -1);
}

template <> 
inline double LuaScript::unlua_getValue<double>(const std::string& variableName_) {
	if(!lua_isnumber(luaState, -1)) {
		Log(WARN) << "'" << variableName_ << "' is not a number!";
	}
	return (double)lua_tonumber(luaState, -1);
}

template <>
inline int LuaScript::unlua_getValue<int>(const std::string& variableName_) {
	if(!lua_isnumber(luaState, -1)) {
		Log(WARN) << "'" << variableName_ << "' is not a number!";
	}
	return (int)lua_tonumber(luaState, -1);
}

template <>
inline std::string LuaScript::unlua_getValue<std::string>(const std::string& variableName_) {
	std::string s = "null";
	if(lua_isstring(luaState, -1)) {
		s = std::string(lua_tostring(luaState, -1));
	} else {
		Log(DEBUG) << "'" << variableName_ << "' is not a string!";
	}
	return s;
}
