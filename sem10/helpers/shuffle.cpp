std::random_device rd;
std::mt19937 g(rd());
std::shuffle(positions.begin(), positions.end(), g);
