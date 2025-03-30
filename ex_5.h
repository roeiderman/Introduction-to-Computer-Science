#define MAX_WORKERS 50
#define MAX_PROJECTS 100
#define JOIN_COMPANY 1
#define NEW_PROJECT 2
#define JOIN_PROJECT 3
#define DISPLAY_PROJ 4
#define DISPLAY_WORKERS 5
#define CHANGE_PROJ 6
#define LEAVE_COMPANY 7
#define EXIT 8
#define MAX_PROJ_WORKERS 4
#define ADD_REMOVE 8


// Forward declarations
typedef struct Worker Worker;
typedef struct FeatureNode FeatureNode;
typedef struct Project Project;

struct Worker
{
    char *name;
    Project **projects;
    int projectCount;
};

struct FeatureNode
{
    char *feature;
    struct FeatureNode *next;
};

struct Project
{
    char *name;
    Worker **workers;
    int workerCount;
    FeatureNode *features;
};

