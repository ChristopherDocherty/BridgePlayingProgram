#include "views/bridge/bridgeTerminalView.hpp"

#include "models/bridge/bridgeGamestateLoader.hpp"

#include <iostream>

#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>

#include <catch2/catch_test_macros.hpp>

namespace Bridge {
auto getRowView(std::string gamestateStr) {

  return gamestateStr | ranges::views::split('\n') |
         ranges::views::transform(
             [](auto s) { return ranges::to<std::string>(s); }) |
         ranges::to<std::vector>;
}

TEST_CASE("Gamestate is displayed correctly") {

  auto expGamestate = loadGamestate("testBoards.json", "default_board_config");
  REQUIRE(expGamestate);
  BridgeGamestate gamestate = *expGamestate;

  std::vector<std::string> expectedView = {
      {"6S by S"},
      {"S leads this trick"},
      {"                  S  K 9 4 3"},
      {"                  H  7 3"},
      {"                  D  Q 8 7 2"},
      {"                  C  Q 8 2"},
      {""},
      {"S                              S  J 10 8"},
      {"H  Q 10 8 5                    H  J 6"},
      {"   4 2                         D  A K 9 6"},
      {"D  J 10 5                         3"},
      {"C  A 10 7 3                    C  J 9 4"},
      {""},
      {"                  S  A Q 7 6"},
      {"                     5 2"},
      {"                  H  A K 9"},
      {"                  D  4"},
      {"                  C  K 6 5"}};

  std::string gamestateStr = BridgeTerminalView::getGamestateString(gamestate);
  std::vector<std::string> rowView = getRowView(gamestateStr);

  ranges::for_each(ranges::views::zip(rowView, expectedView), [](auto views) {
    const auto& [generatedRow, expectedRow] = views;
    CHECK(generatedRow == expectedRow);
  });
}

TEST_CASE("Gamestate with played cards is displayed correctly") {

  auto expGamestate = loadGamestate("testBoards.json", "default_board_config");
  REQUIRE(expGamestate);
  BridgeGamestate gamestate = *expGamestate;

  REQUIRE(gamestate.makeMove("S", "A"));
  REQUIRE(gamestate.makeMove("H", "Q"));
  REQUIRE(gamestate.makeMove("S", "9"));

  std::vector<std::string> expectedView = {
      {"6S by S"},
      {"S leads this trick"},
      {"                  S  K 4 3"},
      {"                  H  7 3"},
      {"                  D  Q 8 7 2"},
      {"                  C  Q 8 2"},
      {""},
      {"S                      S 9     S  J 10 8"},
      {"H  10 8 5 4        H Q         H  J 6"},
      {"   2                   S A     D  A K 9 6"},
      {"D  J 10 5                         3"},
      {"C  A 10 7 3                    C  J 9 4"},
      {""},
      {"                  S  Q 7 6 5"},
      {"                     2"},
      {"                  H  A K 9"},
      {"                  D  4"},
      {"                  C  K 6 5"}};

  std::string gamestateStr = BridgeTerminalView::getGamestateString(gamestate);
  std::vector<std::string> rowView = getRowView(gamestateStr);

  ranges::for_each(ranges::views::zip(rowView, expectedView), [](auto views) {
    const auto& [generatedRow, expectedRow] = views;
    CHECK(generatedRow == expectedRow);
  });
}

}  // namespace Bridge
