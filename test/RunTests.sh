#!/usr/bin/env dash

set -e

UNITY_ROOT="./Unity"
UNITY_SRC="${UNITY_ROOT}/src"
UNITY_FIXTURE="${UNITY_ROOT}/extras/fixture/src"
PROJECT=".."
TEST_RUNNERS='test_runners'

cleanup () {
	rm -rf ${TEST_RUNNERS} a.out*
}
trap cleanup EXIT

mkdir -p ${TEST_RUNNERS}

cc -I ${UNITY_SRC} -I ${UNITY_FIXTURE} -c ${UNITY_SRC}/unity.c
cc -I ${UNITY_SRC} -I ${UNITY_FIXTURE} -c ${UNITY_FIXTURE}/unity_fixture.c

export CFLAGS="-g -fsanitize=address -I ${PROJECT}/inc -I ${UNITY_SRC} -I ${UNITY_FIXTURE}"

# Utils for tests
cc -c utils.c $CFLAGS

# Compile & Run each tests
for test_file in $(find . -maxdepth 1 -type f -name 'Test*.c');
do
	test_name=$(basename ${test_file} '.c')
	echo "========== ${test_name} =========="
	runner=${test_name}_Runner.c

	ruby "$UNITY_ROOT/auto/generate_test_runner.rb" $test_file ${TEST_RUNNERS}/${test_name}_Runner.c
	cc $CFLAGS \
		unity.o \
		unity_fixture.o \
		utils.o \
		${test_file} \
		${TEST_RUNNERS}/${runner} \
		${PROJECT}/lib42.a && ./a.out | grep -E --color 'FAIL|$'
	echo
done
