all: hw1_naive hw1_kmp

CC = gcc

hw1_naive: hw1_naive.c
	$(CC) -o $@ $<

hw1_kmp: hw1_kmp.c
	$(CC) -o $@ $<

clean:
	rm -f $(OBJECT) $(TARGET)
