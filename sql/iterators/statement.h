#ifndef SQL_ITERATORS_STATEMENT_H_
#define SQL_ITERATORS_STATEMENT_H_

#include "sql/parser/ast.h"

#include <string>
#include <vector>

#include "sql/sql_class.h"

#ifndef SessionContext
#define SessionContext THD
#endif

using std::byte;
using std::string;
using std::vector;
namespace ast = parser::ast;

namespace iterators {

/**
  ColumnInfo contains the information of a column.
 */
struct ColumnInfo {
  string schema;
  string table;
  string original_table;
  string name;
  string original_name;
  int column_length;
  uint16_t flag;
  uint64_t default_value_length;
  vector<byte> default_value;
};

/**
  ResultSet represents an result set iterator, which can be used to retrieve the
  query result.
 */
class ResultSet {
  vector<ColumnInfo> Columns();
  int Read();
  bool Close();
  bool IsClosed();
};

/**
  Statement represents an executable statement, which contains a physical plan
  and will build the lower level iterators while its Execute method calling.
 */
class Statement {
  ResultSet Execute();
};

namespace compiler {

/**
  Compile compiles a abstract syntax tree into an executable statement.
  @param node
  @return
 */
Statement Compile(const SessionContext &sctx, const ast::Node &node);

}  // namespace compiler
}  // namespace iterators

#endif  // SQL_ITERATORS_STATEMENT_H_
