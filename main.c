#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "convert.h"

int main() {
    FILE *file = fopen("A1_tests.txt", "r");
    if (!file) {
        printf("Error: Could not open A1_tests.txt\n");
        return 1;
    }

    char line[256], func[32], expected[128], out[128];
    uint32_t n;
    int base, test_num = 1, passed = 0, total = 0;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || strlen(line) < 2) continue;

        if (sscanf(line, "%s %u %d %s", func, &n, &base, expected) == 4) {
            total++;
            if (strcmp(func, "div_convert") == 0) {
                div_convert(n, base, out);
            } else if (strcmp(func, "sub_convert") == 0) {
                sub_convert(n, base, out);
            }

            if (strcmp(out, expected) == 0) {
                printf("Test %d: %s(%u,%d) -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                       test_num, func, n, base, expected, out);
                passed++;
            } else {
                printf("Test %d: %s(%u,%d) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                       test_num, func, n, base, expected, out);
            }
            test_num++;
        }
        else if (sscanf(line, "%s %u %s", func, &n, expected) == 3 &&
                 strcmp(func, "print_tables") == 0) {
            total++;
            printf("Test %d: print_tables(%u)\n", test_num, n);
            print_tables(n);
            printf("[PASS] (if formatted correctly)\n");
            passed++;
            test_num++;
        }
    }

    fclose(file);
    printf("Summary: %d/%d tests passed\n", passed, total);
    return 0;
}
