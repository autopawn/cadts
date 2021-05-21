
GCCFLAGS = -g -std=c99 -Wall

.PHONY: compile run run-test


run: compile
	for ex in ./bin/*; do echo "================== $$ex =================="; $$ex; echo ""; done

run-test: compile
	for ex in ./bin/*; do echo "================== $$ex =================="; valgrind $$ex; echo ""; done

compile:
	mkdir -p bin
	for ex in examples/*.c tests/*.c; do \
		gcc $(GCCFLAGS) $$ex -o bin/$$(basename $$ex | cut -d'.' -f1) ;\
	done
