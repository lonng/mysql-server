# Copyright (c) 2006, 2022, Oracle and/or its affiliates.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License, version 2.0,
# as published by the Free Software Foundation.
#
# This program is also distributed with certain software (including
# but not limited to OpenSSL) that is licensed under separate terms,
# as designated in a particular file or component or in included license
# documentation.  The authors of MySQL hereby grant you an additional
# permission to link the program and your derivative works with the
# separately licensed software that they have included with MySQL.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License, version 2.0, for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA

SET(PARSER_LIB_NAME mysql_parser)

SET(SQL_PARSER_SOURCES
  ast.cc
)

SET(GEN_SOURCES
  ${CMAKE_CURRENT_BINARY_DIR}/parser_yacc.yy.h
  ${CMAKE_CURRENT_BINARY_DIR}/parser_yacc.cc
)

SET_SOURCE_FILES_PROPERTIES(
  ${GEN_SOURCES}
  PROPERTIES GENERATED 1
)

BISON_TARGET(mysql_new_parser
  parser_yacc.yy
  ${CMAKE_CURRENT_BINARY_DIR}/parser_yacc.cc
  COMPILE_FLAGS
  "--name-prefix=MYSQL --yacc ${BISON_FLAGS_WARNINGS} ${BISON_NO_LINE_OPT}"
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser_yacc.yy.h
)

MESSAGE(STATUS "BISON outputs ${BISON_mysql_new_parser_OUTPUTS}")

# Some targets, for easier debugging.
# The new Xcode build system does not support multiple targets that
# DEPEND on the same outputs.
IF(NOT APPLE_XCODE)
  ADD_CUSTOM_TARGET(GenBison_mysql_new_parser DEPENDS ${BISON_mysql_new_parser_OUTPUTS})
ENDIF()

ADD_LIBRARY(${PARSER_LIB_NAME} STATIC
  ${GEN_SOURCES}
  ${SQL_PARSER_SOURCES}
)
