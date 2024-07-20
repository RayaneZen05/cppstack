#include <iostream>
using namespace std;
template <typename T>
class stack {
    public:
        stack(); // base constructor
        stack(size_t stksize); // constructor with stack size given

        //getters
        // returns stack base pointer
        T* getBP() const;
        // returns copy of element at stack top
        T top() const;
        // returns stack top pointer
        T* getSP() const;
        /** pushes parameter value to the stack
         *  @param v: value to be pushed
         *  @returns: stack top pointer
         */
        T* push(T v);
        /** pops top value from the stack 
         *  @reutrns: stack top pointer
        */
        T* pop();
        /** sets new base for stack to sp
         * @returns pointer to bp
         */
        T* setBP();
        // frees allocated memory block
        void free();

    private:
        size_t bpos; // pos of stack base
        size_t pos; // pos of stack top
        size_t size; // size of stack
        T* stk; // stack
        T* BP;  // stack base pointer
        T* SP; // stack top pointer

        // doubles stack size
        void resize() {
            stk = (T*)realloc(stk, size*2);
            size *= 2;
            // reset BP and SP to correct position in new block
            SP = &stk[pos]; // ? note interessante : l'indexing de l'array stk renvoie la valeur a la position donnée, et déréférence donc stk[position]
            BP = &stk[bpos];
        }
};