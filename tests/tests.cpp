#include <gtest/gtest.h>

#include "../src/notes.h"

constexpr char NOTES_OK[] = "../tests/notes_ok.txt";
constexpr char NOTES_BAD[] = "../tests/notes_bad.txt";
constexpr char NOTES_EMPTY[] = "../tests/notes_empty.txt";
constexpr char NO_FILE[] = "no_file.txt";

my::Notes notes;

TEST(Notes, test_read_file_1) {
  EXPECT_NO_THROW(notes.LoadNotes());
  EXPECT_EQ(notes.GetAmountNotes(), 2);
}

TEST(Notes, test_read_file_2) {
  notes.SetFilename(NO_FILE);
  EXPECT_ANY_THROW(notes.LoadNotes());
  EXPECT_EQ(notes.GetAmountNotes(), 0);
}

TEST(Notes, test_validate_file_1) {
  notes.SetFilename(NOTES_OK);
  notes.LoadNotes();
  notes.ValidateFile();
  EXPECT_TRUE(notes.GetReadfile());
}

TEST(Notes, test_validate_file_2) {
  notes.SetFilename(NOTES_BAD);
  notes.LoadNotes();
  notes.ValidateFile();
  EXPECT_FALSE(notes.GetReadfile());
}

TEST(Notes, test_validate_file_3) {
  notes.SetFilename(NOTES_EMPTY);
  notes.LoadNotes();
  notes.ValidateFile();
  EXPECT_FALSE(notes.GetReadfile());
}

TEST(Notes, test_check_amount_notes_1) {
  notes.SetFilename(NOTES_OK);
  notes.LoadNotes();
  EXPECT_TRUE(notes.CheckAmountNotes());
}

TEST(Notes, test_check_amount_notes_2) {
  notes.SetFilename(NOTES_EMPTY);
  notes.LoadNotes();
  EXPECT_FALSE(notes.CheckAmountNotes());
}

TEST(Notes, test_check_note_num_1) {
  notes.SetFilename(NOTES_OK);
  notes.LoadNotes();
  EXPECT_TRUE(notes.CheckNoteNum(1));
}

TEST(Notes, test_check_note_num_2) {
  notes.SetFilename(NOTES_OK);
  notes.LoadNotes();
  EXPECT_FALSE(notes.CheckNoteNum(-1));
}

TEST(Notes, test_check_note_num_3) {
  notes.SetFilename(NOTES_OK);
  notes.LoadNotes();
  EXPECT_FALSE(notes.CheckNoteNum(10));
}

TEST(Notes, test_save_notes_1) {
  notes.SetFilename(NOTES_OK);
  notes.LoadNotes();
  EXPECT_NO_THROW(notes.SaveNotes());
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "en_US.UTF-8");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
