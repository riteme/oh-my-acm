/**
 * title: 快速读入
 * category: 未分类
 * description: mmap.md
 */
#include <unistd.h>  // STDIN_FILENO
#include <sys/mman.h>  // mmap, munmap
#include <cctype>  // isdigit
static struct Reader {
#define BUFSIZE 4194304  // 4MB
	size_t cur, pos;
	char *buf;
	Reader() : cur(BUFSIZE), pos(0), buf(NULL) {}
	char getc() {
		if (cur == BUFSIZE) {
			cur = 0;
			if (buf)
				munmap(buf, BUFSIZE);
			buf = (char*) mmap(
				NULL, BUFSIZE, PROT_READ, MAP_PRIVATE, STDIN_FILENO, pos
			);
			pos += BUFSIZE;
		}
		return buf[cur++];
	}
	template <typename T>
	void read(T &x) {
		char c;
		x = 0;
		do c = getc(); while (!isdigit(c));
		do {
			x = x * 10 + c - '0';
			c = getc();
		} while (isdigit(c));
	}
	template <typename T>
	void operator()(T &x) { read(x); }
	template <typename T, typename ... TArgs>
	void operator()(T &x, TArgs& ...args) {
		read(x); (*this)(args...);
}} read;  // read(u, v, w);
