#include "../src/Parser.h"
#include "gtest/gtest.h"

TEST(PARSER_TEST,READ_LINE){
	Parser parser("echo a b c");
	ASSERT_EQ(parser.line,"echo a b c");
}

TEST(PARSER_TEST,REMOVE_COMMENT){
	Parser parser("echo a b c # comment");
	parser.remove_comment();
	ASSERT_EQ(parser.line,"echo a b c ");
}

TEST(SEPARATION_TEST, POST_FIX_ONE){
	Parser parser("echo a");
	parser.paren();
	parser.parseConnectors();
	vector<string>& v = parser.parsedCmds;
	ASSERT_EQ(v.size(),2);
	ASSERT_EQ(v[0], "echo");
	ASSERT_EQ(v[1],"a");
}

TEST(SEPARATION_TEST, POST_FIX_TWO){
        Parser parser("echo \"a b\" \"# test\"");
        parser.paren();
        parser.parseConnectors();
        vector<string>& v = parser.parsedCmds;
        ASSERT_EQ(v.size(),3);
        ASSERT_EQ(v[0], "echo");
        ASSERT_EQ(v[1],"a b");
	ASSERT_EQ(v[2],"# test");
}

TEST(SEPARATION_TEST, POST_FIX_THREE){
        Parser parser("echo \"a b\" \"# d e\" # test");
        parser.paren();
        parser.parseConnectors();
        vector<string>& v = parser.parsedCmds;
        ASSERT_EQ(v.size(),5);
        ASSERT_EQ(v[0], "echo");
        ASSERT_EQ(v[1],"a b");
	ASSERT_EQ(v[2],"# d e");
}
/*

TEST(PARSER,SPLIT2){
	Parser parser("echo \"a b\" \"# test\"");
	parser.split();
	vector<string>& v = parser.string_list;
	ASSERT_EQ(v.size(),3);
	ASSERT_EQ(v[0],"echo");
	ASSERT_EQ(v[1],"a b");
	ASSERT_EQ(v[2],"# test");
}


TEST(PARSER,SPLIT3){
	Parser parser("echo \"a b\" \"# d e\" # test");
	parser.split();
	vector<string>& v = parser.string_list;
	ASSERT_EQ(v.size(),5);
	ASSERT_EQ(v[0],"echo");
	ASSERT_EQ(v[1],"a b");
	ASSERT_EQ(v[2],"# d e");
}
*/
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
