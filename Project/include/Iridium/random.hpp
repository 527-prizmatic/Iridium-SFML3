#ifndef IRIDIUM_RANDOM_HPP_
#define IRIDIUM_RANDOM_HPP_

#include "Iridium/libraries.hpp"

namespace iridium {
	namespace Random {
		/// @return Uniformly random 32-bit integer
		int integer32();

		/// @return Uniformly random 32-bit integer within [0, _max)
		/// @note If _max is inferior or equal to 0, this function returns 0.
		int range(int _max);
		
		/// @return Uniformly random 32-bit integer within [_min, _max)
		/// @note If _max is inferior or equal to _min, this function returns _min.
		int range(int _min, int _max);

		/// @param _chance Probability to return true, clamped between 0 and 1
		/// @return True with the given probability; false otherwise
		bool chance(float _chance);

		/// @brief Computes an idealized dice roll result.
		/// @param _count Number of dice to roll
		/// @param _size Number of sides to each die
		/// @note If _count is inferior or equal to 0, or if _size is inferior or equal to 1, this function returns 0.
		int diceRoll(int _count, int _size);
		
		/// @brief Computes an idealized dice roll result.
		/// @param _roll Text notation of a die roll in the form XdY, where X is the number of dice to roll and Y the number of sides
		/// @note If for any reason the provided string is not a valid die roll, this function returns 0.
		int diceRoll(std::string _roll);
	}
}




#endif // IRIDIUM_RANDOM_HPP_