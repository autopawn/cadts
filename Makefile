
.PHONY: run-test

run-tests:
	mkdir -p bin
	for ex in examples/*.c tests/*.c; do gcc -std=c99 $$ex -o bin/$$(basename $$ex | cut -d'.' -f1); done
	for ex in ./bin/*; do $$ex; done
