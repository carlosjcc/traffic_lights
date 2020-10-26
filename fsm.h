#define go_east   0
#define wait_east 1
#define go_north   2
#define wait_north 3
#define walk 4

// Linked data structure
struct state_st {
    unsigned long cross_roads;
    unsigned long walk_way;    
    unsigned long time;  
    //unsigned long next[5];
    unsigned long next[1];
};

typedef const struct state_st state;

state fsm[5] = {
    {0x0C, 0x02, 0x00FFFFFF, {wait_east}},
    {0x14, 0x02, 0x00FFFFFF, {go_north}},
    {0x21, 0x02, 0x00FFFFFF, {wait_north}},
    {0x22, 0x02, 0x00FFFFFF, {walk}},
    {0x24, 0x08, 0x00FFFFFF, {go_east}}
};
