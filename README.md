This is a demonstration of using Q Learning to play flappy bird.

Basic overview of how it works:
Q Learning uses Q tables which are just arrays. The Q tables contain values for different actions at different states. The agent performs the highest value action at its state. The agent is trained by interacting with its environment and using rewards or penalties. In this case, the bird getting a point is a reward and dying is a penalty. The algorithm also takes into account potential rewards at future states.