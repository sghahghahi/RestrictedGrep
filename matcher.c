#include "matcher.h"
#include <stdbool.h>

/**
 * Returns true if partial_line matches pattern, starting from the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
	// Base case
	if (*pattern == '\0') return true;

	// If *pattern is a special character
	if (*pattern == '.') {
		if (*partial_line != '\0') {
			return matches_leading(partial_line + 1, pattern + 1);
		}
		return false;

	} else if (*(pattern + 1) == '?') {
		if (*partial_line == *pattern) {
			return matches_leading(partial_line + 1, pattern + 2);
		}
		return matches_leading(partial_line, pattern + 2);

	} else if (*pattern == '+') {
		char prev_char = *(pattern - 1);
		while (*partial_line != '\0' && *partial_line == prev_char) {
			partial_line++;
		}
		return matches_leading(partial_line, pattern + 1);

	} else if (*pattern == '\\') {
		if (*partial_line == *(pattern + 1)) {
			return matches_leading(partial_line + 1, pattern + 2);
		}
		return false;

	// If *pattern is not a special character
	} else {
		if (*partial_line == *pattern) {
			return matches_leading(partial_line + 1, pattern + 1);
		}
		return false;
	}

	return false;
}

int rgrep_matches(char *line, char *pattern) {
	while (*line != '\0') {
		if (matches_leading(line, pattern)) return true;
		line++;
	}

	return false;
}
