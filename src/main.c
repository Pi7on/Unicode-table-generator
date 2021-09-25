#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tag(FILE* fp, char* tag) {
    if (strcmp(tag, "td") == 0) {
        fprintf(fp, "<%s>", tag);
    } else {
        fprintf(fp, "<%s>\n", tag);
    }
}

int main(void) {
    FILE* fp = fopen("..\\..\\data\\unicode_table.html", "wt");

    if (!fp) {
        fprintf(stderr, "could not generate output file.\n");
        exit(1);
    }

    tag(fp, "html");
    tag(fp, "head");
    fprintf(fp, "<link rel=\"stylesheet\" href=\"style2.css\">");
    tag(fp, "/head");
    tag(fp, "body");

    char pre[3];
    pre[0] = '&';
    pre[1] = '#';
    tag(fp, "table");
    tag(fp, "thead");
    tag(fp, "tr");
    fprintf(fp, "<th></th><th>0</th><th>1</th><th>2</th><th>3</th><th>4</th><th>5</th><th>6</th><th>7</th><th>8</th><th>9</th><th>A</th><th>B</th><th>C</th><th>D</th><th>E</th><th>F</th>");
    tag(fp, "/tr");
    tag(fp, "/thead");

    int row = 0;
    for (int i = 0; i < 69631 * 16; i++) {
        if (i % 16 == 0) {
            if (i != 0) {
                tag(fp, "/tr");
            }
            tag(fp, "tr");

            fprintf(fp, "<td>0x%06X</td>", row);
            row += 0x10;
        }

        tag(fp, "td");
        fprintf(fp, "%s%d;", pre, i);
        tag(fp, "/td");

        if (i == (2 * 16) - 1) {
            tag(fp, "/tr");
        }
    }
    tag(fp, "/table");
    tag(fp, "/body");
    tag(fp, "/html");

    fclose(fp);

    return 0;
}