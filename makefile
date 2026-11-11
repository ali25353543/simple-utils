all:
	for f in $$(ls *.c); do \
		gcc -o $${f%.c} $$f; \
	done
