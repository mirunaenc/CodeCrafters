#pragma once
#include <vector>
#include <optional>
#include <fstream>
#include <array>
#include <iostream>
#include "pylon.h"
#include "bridge.h"
#include "board.h"
#include "utility.h"

namespace twixt {

	 class Player {

	public:
		/*enum class EColor : uint8_t
		{
			RED,
			BLACK
		};*/
	private:
		uint16_t m_nrOfAvailablePylons;
		uint16_t m_nrOfAvailableBridges;
		EColor m_color;
		Board& m_gameBoard;

	public:
		Player(uint16_t nrPylons, uint16_t nrBridges, EColor color, Board& gameBoard);
		Player(const Player& otherPlayer) = default;
		Player(Player&& otherPlayer) noexcept = default;
		Player& operator=(Player&& otherPlayer) noexcept;
		Player& operator=(const Player& otherPlayer);
		~Player() = default;

		uint16_t getNrOfAvailablePylons() const;
		void setNrOfAvailablePylons(uint16_t nrPylons);

		uint16_t getNrOfAvailableBridges() const;
		void setNrOfAvailableBridges(uint16_t nrBridges);

		EColor getColor() const;
		void setColor(const EColor& color);

		const Board& getGameBoard() const;
		void setGameBoard(const Board& gameBoard);

		void placePylon(uint16_t line, uint16_t column);

		void placeBridge(const Pylon& start, const Pylon& end);

		bool isWinner();

		void makeMove();

		void savePlayerState(std::ofstream& file) const;
		void loadPlayerState(std::ifstream& file);
		bool positionIsNotCorner(uint16_t line, uint16_t column);
		bool positionIsEnemySide(uint16_t line, uint16_t column);
		void getUserInputAndPlacePylon();
		void updateBridges();
	};
}