#ifndef INC_5_ARCHIVE_FUNCTIONS_H
#define INC_5_ARCHIVE_FUNCTIONS_H

#include <vector>
#include <string>

int copy_data(struct archive *ar, struct archive *aw);

void extract(const std::string &filename);

std::string read_archive_entries(const std::string &path);

#endif //INC_5_ARCHIVE_FUNCTIONS_H
