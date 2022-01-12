- Use compilation database to run tools
- Visit AST
- Collect library features
	- Compare feature location with stdlib path

ast-dump command example:
```
/opt/llvm_13/bin/clang-check --ast-dump fancy_ptr.cpp \ --extra-arg="-I/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include" |  \
gsed -e 's/\x1b\[[0-9;]\{1,6\}m//g'  > ast_dump.log
```