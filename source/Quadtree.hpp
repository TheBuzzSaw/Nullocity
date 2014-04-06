#ifndef QUADTREE_HPP
#define QUADTREE_HPP


class Quadtree
{
    public:
        Quadtree();
        ~Quadtree();

    protected:
    private:
        Quadtree(const Quadtree&) = delete;
        Quadtree& operator=(const Quadtree&) = delete;

        Quadtree* _subtrees[4];
};

#endif
