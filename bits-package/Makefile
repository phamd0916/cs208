bits: bits.c main.c
	gcc -Wall -Werror -O0 -g -o $@ $^

test: test-lower test-upper test-middle

test-lower: bits
	@./bits to_lower "ThIs iS TEst 234)!" > to_lower_out.txt
	@diff to_lower_out.txt to_lower_expected.txt;\
        if [ $$? -eq 0 ]; then echo "to_lower test 1 PASSED"; else echo "to_lower test 1 FAILED"; fi
	@echo

test-upper: bits
	@./bits to_upper "ThIs iS TEst 234)!" > to_upper_out.txt
	@diff to_upper_out.txt to_upper_expected.txt;\
        if [ $$? -eq 0 ]; then echo "to_upper test 1 PASSED"; else echo "to_upper test 1 FAILED"; fi
	@echo

test-middle: bits
	@./bits middle_bits 23 18 4 > middle_bits_out.txt
	@diff middle_bits_out.txt middle_bits_expected.txt;\
        if [ $$? -eq 0 ]; then echo "middle_bits test 1 PASSED"; else echo "middle_bits 1 FAILED"; fi
	@echo

clean:
	rm bits
	rm to_lower_out.txt
	rm to_upper_out.txt
	rm middle_bits_out.txt

