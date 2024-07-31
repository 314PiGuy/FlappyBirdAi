class Bird{
    private:
    public:
    double vy; //since its a sidescroller the bird only has vertical motion
    double pos[2];
    double size;
    Bird(double s);
    void flap();
    void move(); //will apply acceleration and move by the vertical velocity
    void reset(); //will be called when game over and will reset the bird
};
