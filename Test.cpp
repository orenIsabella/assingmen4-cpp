/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */


#include <iostream>

using namespace std;

#include "calculate.hpp"
#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#define COMMA ,

using namespace bullpgia;

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		// BASIC TESTS - DO NOT CHANGE
		ConstantChooser c1235{"1235"}, c12345{"12345"}, c5674{"5674"}, c0000{"0000"}, c1234{"1234"}, c5555{"5555"}, c5634{"5634"};
		ConstantGuesser g1234{"1234"}, g4567{"4567"}, g9999{"9999"}, g3412{"3412"}, g5555{"5555"}, g1134{"1134"}, g5678{"5678"}, g5643{"5643"};
		ConstantChooser c9999{"9999"};
		ConstantGuesser g12345{"12345"};
		ConstantChooser c45678{"45678"}, c45678111{"45678111"}, c1000{"1000"}, c11{"11"}, c123456789{"123456789"}, c98765{"98765"};
		ConstantGuesser g45678{"45678"}, g45678111{"45678111"}, g19{"19"}, g1234567890{"1234567890"}, g9876{"9876"};

		testcase.setname("Calculate bull and pgia")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
		;

		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
		;

		testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=10, true);  // smarty should always win in at most 10 turns!
		}
		//our tests:
		testcase.setname("Calculate bull and pgia")
		.CHECK_OUTPUT(calculateBullAndPgia("12354","12345"), "3,2")    // 3 bull, 2 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("567459","456758"), "1,4")  // 1 bull, 4 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("0000","9999"), "0,0")      // 0 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","3412"), "0,4")      // 0 bull, 4 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("5555","5555"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1034"), "3,0")      // 3 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("5634","5678"), "2,0")      // 2 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("5634","5643"), "2,2")      // 2 bull, 2 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1","5"), "0,0")            // 0 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("12333333777781782737747599983002988478434433245980645646", "12598064333777781782737747599983002988478434433333245646"), "17,39")  // 17 bull, 39 pgia    
		.CHECK_OUTPUT(calculateBullAndPgia("123456789123456789","023456789123456789"), "17,0") // 17 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("21","11"), "1,0")                                  // 1 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("0000002211333333", "3330003330002211"), "3,13")    // 3 bull, 13 pgia  
		.CHECK_OUTPUT(calculateBullAndPgia("9909909","999900"), "5,2")  // 5 bull, 2 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("",""), "0,0")		// 0 bull, 0 pgia
			
		;

		
		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c45678, g45678, 5, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c45678111, g45678111, 8, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1000, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c11, g19, 2, 3), 4)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c123456789, g1234567890, 9, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c98765, g9876, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
		;

		testcase.setname("Play with smart guesser");
		
		RandomChooser r;
		SmartGuesser smartestguesser;
	
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(r, smartestguesser, 4, 100)<=10, true);  // smarty should always win in at most 10 turns!
}

    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}
