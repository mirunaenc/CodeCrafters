#pragma once
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>
#include "LargePylon.h"
#include <fstream>
#include <sstream>
#include "pylon.h"
#include "bridge.h"
#include "utility.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget> 
 

namespace twixt {
	class Board {

	private:
		uint16_t m_size;
		std::vector<std::optional<Pylon>> m_boardPylons;
		std::vector<Bridge> m_boardBridges;
	public:
		Board();
		Board(uint16_t size);
		Board(const Board& board);
		Board(Board&& board) noexcept;
		Board& operator=(const Board& board);
		Board& operator=(Board&& board) noexcept;
		uint16_t getSize() const;
		void setSize(uint16_t size);
		void addPylon(uint16_t line, uint16_t column, const std::optional<Pylon>& pylon);
		void addBridge(Bridge& bridge);
		const std::optional<Pylon>& getPylon(uint16_t line, uint16_t column) const;
		void resetPosition(uint16_t line, uint16_t column);
		bool isPositionInsideBoard(uint16_t line, uint16_t column) const;
		bool isPositionOccupied(uint16_t i, uint16_t j);
		void removeBridge(const Bridge& bridge);
		void provisionalPrint();
		const std::vector<std::optional<Pylon>>& getPylons() const;
		const std::vector<Bridge>& getBridges() const;
		bool isValidBridge(const Pylon& start, const Pylon& end);
		void resetBoard();
		bool canPlaceLargePylon(const LargePylon& pylon);
		bool existsBridgeBetweenPylons(const Pylon& p1, const Pylon& p2);
		bool isPylonOccupied(const Pylon& p);
		bool canPlaceBridge(Pylon& p1, Pylon& p2);
		void createBridge(Pylon& pilon);

		void saveBoardState(std::ofstream& file) const;
		void loadBoardState(std::ifstream& file);

		bool hasRoadDFS(uint16_t currentLine, uint16_t currentColumn, std::vector<bool>& visited);
		EColor hasWinningRoad();
	

		QGraphicsView* createQGraphicsView(QWidget* parent);
		void placePylon(uint16_t line, uint16_t column, EColor color);
	    void printBridges();
	};
}