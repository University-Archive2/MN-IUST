#include <stdio.h>
#include <sys/types.h>
#include <Student.h>

static int write_out(const void *buffer, size_t size, void *app_key) {
    FILE *out_fp = app_key;
    size_t wrote;
    wrote = fwrite(buffer, 1, size, out_fp);
    return (wrote == size) ? 0 : -1;
}
 
int encode(char *filename) {
    Student_t *student;
    student = calloc(1, sizeof(Student_t));
	
    student->id = 401725173;

	PrintableString_t name;
	OCTET_STRING_fromString(&name, "Ali Nazari");
	student->name = name;

	PrintableString_t major;
	OCTET_STRING_fromString(&major, "Computer Engineering");
	student->major = major;

    FILE *fp = fopen(filename, "wb");
    xer_encode(&asn_DEF_Student, student, XER_F_BASIC, write_out, fp);
    fclose(fp);

    fprintf(stderr, "Created %s with XER encoded Student\n", filename);
	xer_fprint(stdout, &asn_DEF_Student, student);
}

int decode(char *filename) {
    char buf[1024];     
    Student_t *student = 0;
    
    FILE *fp = fopen(filename, "rb");
  
    size_t size = fread(buf, 1, sizeof(buf), fp);
    fclose(fp);
 
    asn_dec_rval_t rval = xer_decode(0, &asn_DEF_Student, (void **)&student, buf, size);
	printf("Student ID: %d \t Name: %s \t Major: %s", 
		student->id, student->name.buf, student->major.buf);
}

int main(int ac, char **argv) {
    char *filename = "student.xml";

	char *command = argv[1];
	if (strcmp(command, "encode") == 0) {
		encode(filename);
	} else if (strcmp(command, "decode") == 0) {
		decode(filename);
	} else {
		printf("Please enter encode or decode");
	}
    
    return 0;
}