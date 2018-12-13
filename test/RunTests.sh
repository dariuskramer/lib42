#!/usr/bin/env dash

set -e

UNITY_ROOT="./Unity"
UNITY_SRC="${UNITY_ROOT}/src"
UNITY_FIXTURE="${UNITY_ROOT}/extras/fixture/src"
PROJECT_SRC=".."
TEST_RUNNERS='test_runners'

cleanup () {
	rm -rf ${TEST_RUNNERS} a.out*
}
trap cleanup EXIT

mkdir -p ${TEST_RUNNERS}

for test_file in $(find . -maxdepth 1 -type f -name 'Test*.c');
do
	test_name=$(basename ${test_file} '.c')
	echo "========== ${test_name} =========="
	runner=${test_name}_Runner.c

	ruby "$UNITY_ROOT/auto/generate_test_runner.rb" $test_file ${TEST_RUNNERS}/${test_name}_Runner.c
	cc \
		-g \
		-I ${UNITY_SRC} \
		-I ${UNITY_FIXTURE} \
		-I ${PROJECT_SRC} \
		-fsanitize=address \
		../lib42.a \
		${UNITY_SRC}/unity.o \
		${UNITY_FIXTURE}/unity_fixture.o \
		${test_file} \
		${TEST_RUNNERS}/${runner} && ./a.out | grep -E --color 'FAIL|$'
	echo
done
