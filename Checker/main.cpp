#include <fstream>
#include <string>

enum verdict : unsigned char { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result
{
private:
	FILE * bur;
public:
	enum ext_cls : unsigned char { NO = 1, VERDICT, MESSAGE, TIME, MEMORY, RES_EOF };
	result(bool read = false) { if (read) bur = fopen("result.txt", "r"); else { bur = fopen("result.txt", "w"); } } // bur = stderr;
	~result() { write_type(ext_cls::RES_EOF); fclose(bur); }
	void write_type(ext_cls t) { fwrite(&t, sizeof (t), 1, bur); }
	void write_verdict(verdict v) { write_type(ext_cls::VERDICT); fwrite(&v, sizeof (v), 1, bur); }
	void write_message(std::string str) { write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof (l), 1, bur); fwrite(&str[0], sizeof (str[0]), l, bur); }
	void write_time(long long x) { write_type(ext_cls::TIME); fwrite(&x, sizeof (x), 1, bur); }
	void write_memory(unsigned long long x) { write_type(ext_cls::MEMORY); fwrite(&x, sizeof (x), 1, bur); }
} checker_result;

int main(int argc, const char * argv[]) {

	/* reading from student result file */
	std::ifstream infile("graph.out");

	double studentTime;
	int studentMinWeight;
	infile.read((char*)&studentTime, sizeof(double));
	infile.read((char*)&studentMinWeight, sizeof(int));

	infile.close();

	/* reading from system result file */
	infile = std::ifstream("answer.txt");

	double systemTime;
	int systemMinWeight;
	infile.read((char*)&systemTime, sizeof(double));
	infile.read((char*)&systemMinWeight, sizeof(int));

	infile.close();

	/* Checking correctness and writing result*/
	if (systemMinWeight == studentMinWeight) {
		checker_result.write_message("AC. Minimal weights are equal.");
		checker_result.write_verdict(verdict::AC);
	}
	else {
		checker_result.write_message("WA. Output is not correct");
		checker_result.write_verdict(verdict::WA);
	}
	checker_result.write_time(studentTime * 1e7);
	return 0;
}