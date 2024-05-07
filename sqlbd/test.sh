set -e

./build.sh --test

./bin/Tests --gtest_output=xml:TestsResults.xml
rm test.db
