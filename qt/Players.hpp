#ifndef PLAYERS_HPP
#define PLAYERS_HPP
	enum Player{FirstPlayer , SecondPlayer};
	class Players{
		public:
		static Player oposite(Player player){
			if(player == FirstPlayer){
				return SecondPlayer;
			}
			return FirstPlayer;
		}
	};
#endif
