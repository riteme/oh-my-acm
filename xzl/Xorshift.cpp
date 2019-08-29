typedef unsigned int u32;
typedef unsigned long long u64;
#define ACM_BEGIN
inline u32 mrand32() {
	static u32 x = 19260817;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}
inline u64 mrand64() {
	static u64 x = 0x19260817deedbeef;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}
#define ACM_END
