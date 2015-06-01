/*
 * Meme.cpp
 * What the fuck am I doing with my life...
 *  Created on: May 29, 2015
 *      Author: inferno
 */

#include <util/Meme.h>
#include <ctime>
#include <math.h>

  std::string rng::meme() {
    int r = (std::time(0) + rand()) % 36;
    switch(r) {
      case 0 : return "( ͡° ͜ʖ ͡°)";
      case 1 : return "ಠ_ಠ";
      case 2 : return "( ͠° ͟ʖ ͡°)";
      case 3 : return "ᕦ( ͡° ͜ʖ ͡°)ᕤ";
      case 4 : return "( ͡~ ͜ʖ ͡°)";
      case 5 : return "( ͡o ͜ʖ ͡o)";
      case 6 : return "͡° ͜ʖ ͡ -";
      case 7 : return "( ͡͡ ° ͜ ʖ ͡ °)﻿";
      case 8 : return "( ͡ ͡° ͡°  ʖ ͡° ͡°)";
      case 9 : return "(ง ͠° ͟ل͜ ͡°)ง";
      case 10 : return "( ͡° ͜ʖ ͡ °)";
      case 11 : return "༼ つ ◕_◕ ༽つ";
      case 12 : return "[ ͡° ͜ʖ ͡°]";
      case 13 : return "ヽ༼ຈل͜ຈ༽ﾉ";
      case 14 : return "{ ͡• ͜ʖ ͡•}";
      case 15 : return "( ͡° ͜V ͡°)";
      case 16 : return "( ͡^ ͜ʖ ͡^)";
      case 17 : return "( ‾ʖ̫‾)";
      case 18 : return "( ͡°╭͜ʖ╮͡° )";
      case 19 : return "ᕦ( ͡°╭͜ʖ╮͡° )ᕤ";
      case 20 : return "༼ つ ·̿_·̿ ༽つ";
      case 21 : return "ლ(·̿̿Ĺ̯̿̿·̿ლ)";
      case 22 : return "(╯°□°）╯︵ ┻━┻";
      case 23 : return "(ﾉಥ益ಥ）ﾉ﻿ ┻━┻";
      case 24 : return "┬──┬﻿ ¯\\_(ツ)";
      case 25 : return "┻━┻ ︵ヽ(`Д´)ﾉ︵﻿ ┻━┻";
      case 26 : return "┻━┻ ︵﻿ ¯\\(ツ)/¯ ︵ ┻━┻";
      case 27 : return "┬─┬ノ( º _ ºノ)";
      case 28 : return "ʕ•ᴥ•ʔ";
      case 29 : return "(⌐■_■)";
      case 30 : return "( ͜。 ͡ʖ ͜。)";
      case 31 : return "¯\\_(ツ)_/¯";
      case 32 : return "ಥ_ಥ";
      case 33 : return "༼ ºل͟º ༽";
      case 34 : return "t ( - _ - t )";
      case 35 : return "(ง ͠° ͜ʖ ͡°)ง";
      case 36 : return "(⊙ヮ⊙)";
      default : return ":^)";
    }
  }


