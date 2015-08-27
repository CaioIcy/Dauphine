#ifndef INCLUDE_LUASCRIPT_H
#define INCLUDE_LUASCRIPT_H

/*
https://github.com/CaioIcy/UnLua
https://github.com/EliasD/unnamed_lua_binder
*/

#include "lua.hpp"

#ifndef LUA_OK
#define LUA_OK 0
#endif

#include <string>
#include <vector>

/**
* Parses lua scripts into C++.
*
*/
class LuaScript {

	public:
		/**
		* The constructor.
		* Initializes a new lua state, and loads the desired script.
		* @param filename_ : Path to the desired script, i.e. "lua/level1/Player.lua".
		*/
		LuaScript(const std::string& filename_);

		/**
		* The destructor.
		* Closes the lua state, if open.
		*/
		virtual ~LuaScript();

		/**
		* Gets value of desired variable.
		* Template for the different get methods, which recieve a different type of value.
		* @param variableName_ : The varaible you want to get a value from.
		* @return The T value stored in 'variableName_' inside the lua script.
		*/
		template<typename T>
		T unlua_get(const std::string& variableName_);
		
		/**
		* Gets an int vector.
		* 
		* @param name_ : The table which contains the int vector.
		* @return An int vector, containing all the ints inside the 'name_' array from the lua script.
		*/
		std::vector<int> unlua_getIntVector(const std::string& name_);

		/**
		* Gets the keys from a table.
		*
		* @param name_ : The name of the table.
		* @return A string vector, containing all the keys from inside the 'name_' table from the lua script.
		*/
		std::vector<std::string> unlua_getTableKeys(const std::string& name_);

	private:
		lua_State* luaState; /**< The lua state. */
		int level; /**< Current level. */

		inline void unlua_clean(){
		    int n = lua_gettop(this->luaState);
		    lua_pop(this->luaState, n);
		}

		/**
		* Validates existance of the variable.
		* Checks where the 'variableName_' variable exists inside the lua script.
		* @param variableName_ : The varaible you want to get a value from.
		* @return True for success, false for failure to get variable.
		*/
		bool unlua_getToStack(const std::string& variableName_);		

		/**
		* Gets a T type value from lua script.
		*
		* @param variableName_ : The varaible you want to get a value from.
		* @return T type value.
		*/
		template<typename T>
		T unlua_getValue(const std::string& variableName_);

		/**
		* Gets a default value.
		* 
		* @return Value 0 or a string "null", depending on how it is called.
		*/
		template<typename T>
		T unlua_getDefault();

};

// Template definitions.
#include "LuaScript.tpp"

#endif //INCLUDE_LUASCRIPT_H
