#ifndef YOLOV2_H

#define YOLOV2_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

//#include "yolo_hls.h"

typedef enum{
    LOGISTIC, RELU, RELIE, LINEAR, RAMP, TANH, PLSE, LEAKY, ELU, LOGGY, STAIR, HARDTAN, LHTAN
} ACTIVATION;

typedef enum {
    CONVOLUTIONAL,
    DECONVOLUTIONAL,
    CONNECTED,
    MAXPOOL,
    SOFTMAX,
    DETECTION,
    DROPOUT,
    CROP,
    ROUTE,
    COST,
    NORMALIZATION,
    AVGPOOL,
    LOCAL,
    SHORTCUT,
    ACTIVE,
    RNN,
    GRU,
    LSTM,
    CRNN,
    BATCHNORM,
    NETWORK,
    XNOR,
    REGION,
    YOLO,
    REORG,
    UPSAMPLE,
    LOGXENT,
    L2NORM,
    BLANK
} LAYER_TYPE;

struct network;
typedef struct network network;

struct layer;
typedef struct layer layer;

struct layer{
    LAYER_TYPE type;
    ACTIVATION activation;
    void (*forward)   (struct layer, struct network);
    int batch_normalize;
    int shortcut;
    int batch;
    int forced;
    int flipped;
    int inputs;
    int outputs;
    int nweights;
    int nbiases;
    int extra;
    int truths;
    int h,w,c;
    int out_h, out_w, out_c;
    int n;
    int max_boxes;
    int groups;
    int size;
    int side;
    int stride;
    int reverse;
    int flatten;
    int spatial;
    int pad;
    int sqrt;
    int flip;
    int index;
    int binary;
    int xnor;
    int steps;
    int hidden;
    int truth;
    float smooth;
    float dot;
    float angle;
    float jitter;
    float saturation;
    float exposure;
    float shift;
    float ratio;
    float learning_rate_scale;
    float clip;
    int softmax;
    int classes;
    int coords;
    int background;
    int rescore;
    int objectness;
    int joint;
    int noadjust;
    int reorg;
    int log;
    int tanh;
    int *mask;
    int total;

    float alpha;
    float beta;
    float kappa;

    float coord_scale;
    float object_scale;
    float noobject_scale;
    float mask_scale;
    float class_scale;
    int bias_match;
    int random;
    float ignore_thresh;
    float truth_thresh;
    float thresh;
    float focus;
    int classfix;
    int absolute;

    int onlyforward;
    int stopbackward;
   // int dontload;
    int dontsave;
  //  int dontloadscales;

    float temperature;
    float probability;
    float scale;

    char  * cweights;
    int   * indexes;
    int   * input_layers;
    int   * input_sizes;
    int   * map;
    float * rand;
    float * cost;
    float * state;
    float * prev_state;
    float * forgot_state;
    float * forgot_delta;
    float * state_delta;
    float * combine_cpu;
    float * combine_delta_cpu;

    float * concat;
    float * concat_delta;

    float * binary_weights;

    float * biases;
    float * bias_updates;

    float * scales;
    float * scale_updates;

    float * weights;
    float * weight_updates;

    float * delta;
    float * output;
    float * loss;
    float * squared;
    float * norms;

    float * spatial_mean;
    float * mean;
    float * variance;

    float * mean_delta;
    float * variance_delta;

    float * rolling_mean;
    float * rolling_variance;

    float * x;
    float * x_norm;

    float * m;
    float * v;
    
    float * bias_m;
    float * bias_v;
    float * scale_m;
    float * scale_v;


    float *z_cpu;
    float *r_cpu;
    float *h_cpu;
    float * prev_state_cpu;

    float *temp_cpu;
    float *temp2_cpu;
    float *temp3_cpu;

    float *dh_cpu;
    float *hh_cpu;
    float *prev_cell_cpu;
    float *cell_cpu;
    float *f_cpu;
    float *i_cpu;
    float *g_cpu;
    float *o_cpu;
    float *c_cpu;
    float *dc_cpu; 

    float * binary_input;

    struct layer *input_layer;
    struct layer *self_layer;
    struct layer *output_layer;

    struct layer *reset_layer;
    struct layer *update_layer;
    struct layer *state_layer;

    struct layer *input_gate_layer;
    struct layer *state_gate_layer;
    struct layer *input_save_layer;
    struct layer *state_save_layer;
    struct layer *input_state_layer;
    struct layer *state_state_layer;

    struct layer *input_z_layer;
    struct layer *state_z_layer;

    struct layer *input_r_layer;
    struct layer *state_r_layer;

    struct layer *input_h_layer;
    struct layer *state_h_layer;
	
    struct layer *wz;
    struct layer *uz;
    struct layer *wr;
    struct layer *ur;
    struct layer *wh;
    struct layer *uh;
    struct layer *uo;
    struct layer *wo;
    struct layer *uf;
    struct layer *wf;
    struct layer *ui;
    struct layer *wi;
    struct layer *ug;
    struct layer *wg;

    //tree *softmax_tree;
    size_t workspace_size;
};

void free_layer(layer l)
{
    if(l.cweights)           free(l.cweights);
    if(l.indexes)            free(l.indexes);
    if(l.input_layers)       free(l.input_layers);
    if(l.input_sizes)        free(l.input_sizes);
    if(l.map)                free(l.map);
    if(l.rand)               free(l.rand);
    if(l.cost)               free(l.cost);
    if(l.state)              free(l.state);
    if(l.prev_state)         free(l.prev_state);
    if(l.forgot_state)       free(l.forgot_state);
    if(l.forgot_delta)       free(l.forgot_delta);
    if(l.state_delta)        free(l.state_delta);
    if(l.concat)             free(l.concat);
    if(l.concat_delta)       free(l.concat_delta);
    if(l.binary_weights)     free(l.binary_weights);
    if(l.biases)             free(l.biases);
    if(l.bias_updates)       free(l.bias_updates);
    if(l.scales)             free(l.scales);
    if(l.scale_updates)      free(l.scale_updates);
    if(l.weights)            free(l.weights);
    if(l.weight_updates)     free(l.weight_updates);
    if(l.delta)              free(l.delta);
    if(l.output)             free(l.output);
    if(l.squared)            free(l.squared);
    if(l.norms)              free(l.norms);
    if(l.spatial_mean)       free(l.spatial_mean);
    if(l.mean)               free(l.mean);
    if(l.variance)           free(l.variance);
    if(l.mean_delta)         free(l.mean_delta);
    if(l.variance_delta)     free(l.variance_delta);
    if(l.rolling_mean)       free(l.rolling_mean);
    if(l.rolling_variance)   free(l.rolling_variance);
    if(l.x)                  free(l.x);
    if(l.x_norm)             free(l.x_norm);
    if(l.m)                  free(l.m);
    if(l.v)                  free(l.v);
    if(l.z_cpu)              free(l.z_cpu);
    if(l.r_cpu)              free(l.r_cpu);
    if(l.h_cpu)              free(l.h_cpu);
    if(l.binary_input)       free(l.binary_input);
}

//void free_layer(layer);

typedef enum {
    CONSTANT, STEP, EXP, POLY, STEPS, SIG, RANDOM
} learning_rate_policy;

typedef struct network{
    int n;
    int batch;
    size_t *seen;
    int *t;
    float epoch;
    int subdivisions;
    layer *layers;
    float *output;
    learning_rate_policy policy;

    float learning_rate;
    float momentum;
    float decay;
    float gamma;
    float scale;
    float power;
    int time_steps;
    int step;
    int max_batches;
    float *scales;
    int   *steps;
    int num_steps;
    int burn_in;

    int adam;
    float B1;
    float B2;
    float eps;

    int inputs;
    int outputs;
    int truths;
    int notruth;
    int h, w, c;
    int max_crop;
    int min_crop;
    float max_ratio;
    float min_ratio;
    int center;
    float angle;
    float aspect;
    float exposure;
    float saturation;
    float hue;
    int random;

    int gpu_index;
//    tree *hierarchy;

    float *input;
    float *truth;
    float *delta;
    float *workspace;
    int train;
    int index;
    float *cost;
    float clip;
} network;

network *make_network(int n);
layer get_network_output_layer(network *net);

typedef struct {
    int w;
    int h;
    float scale;
    float rad;
    float dx;
    float dy;
    float aspect;
} augment_args;

typedef struct {
    int w;
    int h;
    int c;
    float *data;
} image;

typedef struct{
    float x, y, w, h;
} box;

typedef struct detection{
    box bbox;
    int classes;
    float *prob;
    float *mask;
    float objectness;
    int sort_class;
} detection;

typedef struct matrix{
    int rows, cols;
    float **vals;
} matrix;


typedef struct{
    int w, h;
    matrix X;
    matrix y;
    int shallow;
    int *num_boxes;
    box **boxes;
} data;

typedef enum {
    CLASSIFICATION_DATA, DETECTION_DATA, CAPTCHA_DATA, REGION_DATA, IMAGE_DATA, COMPARE_DATA, WRITING_DATA, SWAG_DATA, TAG_DATA, OLD_CLASSIFICATION_DATA, STUDY_DATA, DET_DATA, SUPER_DATA, LETTERBOX_DATA, REGRESSION_DATA, SEGMENTATION_DATA, INSTANCE_DATA
} data_type;

typedef struct load_args{
    int threads;
    char **paths;
    char *path;
    int n;
    int m;
    char **labels;
    int h;
    int w;
    int out_w;
    int out_h;
    int nh;
    int nw;
    int num_boxes;
    int min, max, size;
    int classes;
    int background;
    int scale;
    int center;
    int coords;
    float jitter;
    float angle;
    float aspect;
    float saturation;
    float exposure;
    float hue;
    data *d;
    image *im;
    image *resized;
    data_type type;
//    tree *hierarchy;
} load_args;

typedef struct{
    int id;
    float x,y,w,h;
    float left, right, top, bottom;
} box_label;

//network *load_network(char *cfg, char *weights, int clear);
//load_args get_base_args(network *net);
//void free_data(data d);

typedef struct{
    char *key;
    char *val;
    int used;
} kvp;

typedef struct node{
    void *val;
    struct node *next;
    struct node *prev;
} node;

typedef struct list{
    int size;
    node *front;
    node *back;
} list;

void error(const char *s)
{
    perror(s);
    assert(0);
    exit(-1);
}

void malloc_error()
{
    fprintf(stderr, "Malloc error\n");
    exit(-1);
}

void file_error(char *s)
{
    fprintf(stderr, "Couldn't open file: %s\n", s);
    exit(0);
}

/////////////////list begin
list *make_list()
{
	list *l = (list *)malloc(sizeof(list));
	l->size = 0;
	l->front = 0;
	l->back = 0;
	return l;
}


void *list_pop(list *l){
    if(!l->back) return 0;
    node *b = l->back;
    void *val = b->val;
    l->back = b->prev;
    if(l->back) l->back->next = 0;
    free(b);
    --l->size;
    
    return val;
}

void list_insert(list *l, void *val)
{
	node *new_node = (node *)malloc(sizeof(node));
	new_node->val = val;
	new_node->next = 0;

	if(!l->back){
		l->front = new_node;
		new_node->prev = 0;
	}else{
		l->back->next = new_node;
		new_node->prev = l->back;
	}
	l->back = new_node;
	++l->size;
}

void free_node(node *n)
{
	node *next;
	while(n) {
		next = n->next;
		free(n);
		n = next;
	}
}

void free_list(list *l)
{
	free_node(l->front);
	free(l);
}

void free_list_contents(list *l)
{
	node *n = l->front;
	while(n){
		free(n->val);
		n = n->next;
	}
}

void **list_to_array(list *l)
{
    void **a = (void **)calloc(l->size, sizeof(void*));
    int count = 0;
    node *n = l->front;
    while(n){
        a[count++] = n->val;
        n = n->next;
    }
    return a;
}
/////////////////list end

/////////////////////utils begin
void del_arg(int argc, char **argv, int index)
{
    int i;
    for(i = index; i < argc-1; ++i) argv[i] = argv[i+1];
    argv[i] = 0;
}

int find_arg(int argc, char* argv[], char *arg)
{
    int i;
    for(i = 0; i < argc; ++i) {
        if(!argv[i]) continue;
        if(0==strcmp(argv[i], arg)) {
            del_arg(argc, argv, i);
            return 1;
        }
    }
    return 0;
}

int find_int_arg(int argc, char **argv, char *arg, int def)
{
    int i;
    for(i = 0; i < argc-1; ++i){
        if(!argv[i]) continue;
        if(0==strcmp(argv[i], arg)){
            def = atoi(argv[i+1]);
            del_arg(argc, argv, i);
            del_arg(argc, argv, i);
            break;
        }
    }
    return def;
}

float find_float_arg(int argc, char **argv, char *arg, float def)
{
    int i;
    for(i = 0; i < argc-1; ++i){
        if(!argv[i]) continue;
        if(0==strcmp(argv[i], arg)){
            def = atof(argv[i+1]);
            del_arg(argc, argv, i);
            del_arg(argc, argv, i);
            break;
        }
    }
    return def;
}

char *find_char_arg(int argc, char **argv, char *arg, char *def)
{
    int i;
    for(i = 0; i < argc-1; ++i){
        if(!argv[i]) continue;
        if(0==strcmp(argv[i], arg)){
            def = argv[i+1];
            del_arg(argc, argv, i);
            del_arg(argc, argv, i);
            break;
        }
    }
    return def;
}

unsigned char *read_file(char *filename)
{
    FILE *fp = fopen(filename, "rb");
    size_t size;

    fseek(fp, 0, SEEK_END); 
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET); 

    unsigned char *text = (unsigned char *)calloc(size+1, sizeof(unsigned char));
    fread(text, 1, size, fp);
    fclose(fp);
    return text;
}

list *split_str(char *s, char delim)
{
    size_t i;
    size_t len = strlen(s);
    list *l = make_list();
    list_insert(l, s);
    for(i = 0; i < len; ++i){
        if(s[i] == delim){
            s[i] = '\0';
            list_insert(l, &(s[i+1]));
        }
    }
    return l;
}

void strip(char *s)
{
    size_t i;
    size_t len = strlen(s);
    size_t offset = 0;
    for(i = 0; i < len; ++i){
        char c = s[i];
        if(c==' '||c=='\t'||c=='\n') ++offset;
        else s[i-offset] = c;
    }
    s[len-offset] = '\0';
}

void strip_char(char *s, char bad)
{
    size_t i;
    size_t len = strlen(s);
    size_t offset = 0;
    for(i = 0; i < len; ++i){
        char c = s[i];
        if(c==bad) ++offset;
        else s[i-offset] = c;
    }
    s[len-offset] = '\0';
}

void free_ptrs(void **ptrs, int n)
{
    int i;
    for(i = 0; i < n; ++i) free(ptrs[i]);
    free(ptrs);
}

char *fgetl(FILE *fp)
{
    if(feof(fp)) return 0;
    size_t size = 512;
    char *line = (char *)malloc(size*sizeof(char));
    if(!fgets(line, size, fp)){
        free(line);
        return 0;
    }

    size_t curr = strlen(line);

    while((line[curr-1] != '\n') && !feof(fp)){
        if(curr == size-1){
            size *= 2;
            line = (char *)realloc(line, size*sizeof(char));
            if(!line) {
                printf("%ld\n", size);
                malloc_error();
            }
        }
        size_t readsize = size-curr;
        if(readsize > INT_MAX) readsize = INT_MAX-1;
        fgets(&line[curr], readsize, fp);
        curr = strlen(line);
    }
    if(line[curr-1] == '\n') line[curr-1] = '\0';

    return line;
}
/////////////////////utils end

////////////////////option_list begin

void option_insert(list *l, char *key, char *val)
{
    kvp *p = (kvp *)malloc(sizeof(kvp));
    p->key = key;
    p->val = val;
    p->used = 0;
    list_insert(l, p);
}

int read_option(char *s, list *options)
{
    size_t i;
    size_t len = strlen(s);
    char *val = 0;
    for(i = 0; i < len; ++i){
        if(s[i] == '='){
            s[i] = '\0';
            val = s+i+1;
            break;
        }
    }
    if(i == len-1) return 0;
    char *key = s;
    option_insert(options, key, val);
    return 1;
}

void option_unused(list *l)
{
    node *n = l->front;
    while(n){
        kvp *p = (kvp *)n->val;
        if(!p->used){
            fprintf(stderr, "Unused field: '%s = %s'\n", p->key, p->val);
        }
        n = n->next;
    }
}

char *option_find(list *l, char *key)
{
    node *n = l->front;
    while(n){
        kvp *p = (kvp *)n->val;
        if(strcmp(p->key, key) == 0){
            p->used = 1;
            return p->val;
        }
        n = n->next;
    }
    return 0;
}
char *option_find_str(list *l, char *key, char *def)
{
    char *v = option_find(l, key);
    if(v) return v;
    if(def) fprintf(stderr, "%s: Using default '%s'\n", key, def);
    return def;
}

int option_find_int(list *l, char *key, int def)
{
    char *v = option_find(l, key);
    if(v) return atoi(v);
    fprintf(stderr, "%s: Using default '%d'\n", key, def);
    return def;
}

int option_find_int_quiet(list *l, char *key, int def)
{
    char *v = option_find(l, key);
    if(v) return atoi(v);
    return def;
}

float option_find_float_quiet(list *l, char *key, float def)
{
    char *v = option_find(l, key);
    if(v) return atof(v);
    return def;
}

float option_find_float(list *l, char *key, float def)
{
    char *v = option_find(l, key);
    if(v) return atof(v);
    fprintf(stderr, "%s: Using default '%lf'\n", key, def);
    return def;
}

list *read_data_cfg(char *filename)
{
    FILE *file = fopen(filename, "r");
    if(file == 0) file_error(filename);
    char *line;
    int nu = 0;
    list *options = make_list();
    while((line=fgetl(file)) != 0){
        ++ nu;
        strip(line);
        switch(line[0]){
            case '\0':
            case '#':
            case ';':
                free(line);
                break;
            default:
                if(!read_option(line, options)){
                    fprintf(stderr, "Config file error line %d, could parse: %s\n", nu, line);
                    free(line);
                }
                break;
        }
    }
    fclose(file);
    return options;
}
///////////////////option_list end
image make_empty_image(int w, int h, int c)
{
    image out;
    out.data = 0;
    out.h = h;
    out.w = w;
    out.c = c;
    return out;
}

list *get_paths(char *filename)
{
    char *path;
    FILE *file = fopen(filename, "r");
    if(!file) file_error(filename);
    list *lines = make_list();
    while((path=fgetl(file))){
        list_insert(lines, path);
    }
    fclose(file);
    return lines;
}

char **get_labels(char *filename)
{
    list *plist = get_paths(filename);
    char **labels = (char **)list_to_array(plist);
    free_list(plist);
    return labels;
}


image make_image(int w, int h, int c)
{
    image out = make_empty_image(w,h,c);
    out.data = (float *)calloc(h*w*c, sizeof(float));
    return out;
}

static float get_pixel(image m, int x, int y, int c)
{
    assert(x < m.w && y < m.h && c < m.c);
    return m.data[c*m.h*m.w + y*m.w + x];
}

static void set_pixel(image m, int x, int y, int c, float val)
{
    if (x < 0 || y < 0 || c < 0 || x >= m.w || y >= m.h || c >= m.c) return;
    assert(x < m.w && y < m.h && c < m.c);
    m.data[c*m.h*m.w + y*m.w + x] = val;
}

static void add_pixel(image m, int x, int y, int c, float val)
{
    assert(x < m.w && y < m.h && c < m.c);
    m.data[c*m.h*m.w + y*m.w + x] += val;
}

void free_image(image m)
{
    if(m.data){
        free(m.data);
    }
}

image resize_image(image im, int w, int h)
{
    image resized = make_image(w, h, im.c);   
    image part = make_image(w, im.h, im.c);
    int r, c, k;
    float w_scale = (float)(im.w - 1) / (w - 1);
    float h_scale = (float)(im.h - 1) / (h - 1);
    for(k = 0; k < im.c; ++k){
        for(r = 0; r < im.h; ++r){
            for(c = 0; c < w; ++c){
                float val = 0;
                if(c == w-1 || im.w == 1){
                    val = get_pixel(im, im.w-1, r, k);
                } else {
                    float sx = c*w_scale;
                    int ix = (int) sx;
                    float dx = sx - ix;
                    val = (1 - dx) * get_pixel(im, ix, r, k) + dx * get_pixel(im, ix+1, r, k);
                }
                set_pixel(part, c, r, k, val);
            }
        }
    }

    for(k = 0; k < im.c; ++k){
        for(r = 0; r < h; ++r){
            float sy = r*h_scale;
            int iy = (int) sy;
            float dy = sy - iy;
            for(c = 0; c < w; ++c){
                float val = (1-dy) * get_pixel(part, c, iy, k);
                set_pixel(resized, c, r, k, val);
            }
            if(r == h-1 || im.h == 1) continue;
            for(c = 0; c < w; ++c){
                float val = dy * get_pixel(part, c, iy+1, k);
                add_pixel(resized, c, r, k, val);
            }
        }
    }

    free_image(part);
    return resized;
}

void fill_image(image m, float s)
{
    int i;
    for(i = 0; i < m.h*m.w*m.c; ++i) m.data[i] = s;
}

void embed_image(image source, image dest, int dx, int dy)
{
    int x,y,k;
    for(k = 0; k < source.c; ++k){
        for(y = 0; y < source.h; ++y){
            for(x = 0; x < source.w; ++x){
                float val = get_pixel(source, x,y,k);
                set_pixel(dest, dx+x, dy+y, k, val);
            }
        }
    }
}

image letterbox_image(image im, int w, int h)
{
    int new_w = im.w;
    int new_h = im.h;
    if (((float)w/im.w) < ((float)h/im.h)) {
        new_w = w;
        new_h = (im.h * w)/im.w;
    } else {
        new_h = h;
        new_w = (im.w * h)/im.h;
    }
    image resized = resize_image(im, new_w, new_h);
    image boxed = make_image(w, h, im.c);
    fill_image(boxed, .5);
    //int i;
    //for(i = 0; i < boxed.w*boxed.h*boxed.c; ++i) boxed.data[i] = 0;
    embed_image(resized, boxed, (w-new_w)/2, (h-new_h)/2); 
    free_image(resized);
    return boxed;
}

image load_image_stb(char *filename, int channels)
{
    int w, h, c;
    unsigned char *data = stbi_load(filename, &w, &h, &c, channels);
    if (!data) {
        fprintf(stderr, "Cannot load image \"%s\"\nSTB Reason: %s\n", filename, stbi_failure_reason());
        exit(0);
    }
    if(channels) c = channels;
    int i,j,k;
    image im = make_image(w, h, c);
    for(k = 0; k < c; ++k){
        for(j = 0; j < h; ++j){
            for(i = 0; i < w; ++i){
                int dst_index = i + w*j + w*h*k;
                int src_index = k + c*i + c*w*j;
                im.data[dst_index] = (float)data[src_index]/255.;
            }
        }
    }
    free(data);
    return im;
}

void save_image_png(image im, const char *name)
{
    char buff[256];
    //sprintf(buff, "%s (%d)", name, windows);
    sprintf(buff, "%s.png", name);
	unsigned char *data = (unsigned char *)calloc(im.w*im.h*im.c, sizeof(char));
    int i,k;
    for(k = 0; k < im.c; ++k){
        for(i = 0; i < im.w*im.h; ++i){
            data[i*im.c+k] = (unsigned char) (255*im.data[i + k*im.w*im.h]);
        }
    }
    int success = stbi_write_png(buff, im.w, im.h, im.c, data, im.w*im.c);
    free(data);
    if(!success) fprintf(stderr, "Failed to write image %s\n", buff);
}

image **load_alphabet()
{
    int i, j;
    const int nsize = 8;
    image **alphabets = (image **)calloc(nsize, sizeof(image));
    for(j = 0; j < nsize; ++j){
        alphabets[j] = (image *)calloc(128, sizeof(image));
        for(i = 32; i < 127; ++i){
            char buff[256];
            sprintf(buff, "labels/%d_%d.png", i, j);
            //alphabets[j][i] = load_image_color(buff, 0, 0);
			alphabets[j][i] = load_image_stb(buff, 3);
        }
    }
    return alphabets;
}
///////////////////activation begin

static inline float stair_activate(float x)
{
    int n = floor(x);
    if (n%2 == 0) return floor(x/2.);
    else return (x - n) + floor(x/2.);
}
static inline float hardtan_activate(float x)
{
    if (x < -1) return -1;
    if (x > 1) return 1;
    return x;
}
static inline float linear_activate(float x){return x;}
static inline float logistic_activate(float x){return 1./(1. + exp(-x));}
static inline float loggy_activate(float x){return 2./(1. + exp(-x)) - 1;}
static inline float relu_activate(float x){return x*(x>0);}
static inline float elu_activate(float x){return (x >= 0)*x + (x < 0)*(exp(x)-1);}
static inline float relie_activate(float x){return (x>0) ? x : .01*x;}
static inline float ramp_activate(float x){return x*(x>0)+.1*x;}
static inline float leaky_activate(float x){return (x>0) ? x : .1*x;}
static inline float tanh_activate(float x){return (exp(2*x)-1)/(exp(2*x)+1);}
static inline float plse_activate(float x)
{
    if(x < -4) return .01 * (x + 4);
    if(x > 4)  return .01 * (x - 4) + 1;
    return .125*x + .5;
}

static inline float lhtan_activate(float x)
{
    if(x < 0) return .001*x;
    if(x > 1) return .001*(x-1) + 1;
    return x;
}
static inline float lhtan_gradient(float x)
{
    if(x > 0 && x < 1) return 1;
    return .001;
}

static inline float hardtan_gradient(float x)
{
    if (x > -1 && x < 1) return 1;
    return 0;
}
static inline float linear_gradient(float x){return 1;}
static inline float logistic_gradient(float x){return (1-x)*x;}
static inline float loggy_gradient(float x)
{
    float y = (x+1.)/2.;
    return 2*(1-y)*y;
}
static inline float stair_gradient(float x)
{
    if (floor(x) == x) return 0;
    return 1;
}
static inline float relu_gradient(float x){return (x>0);}
static inline float elu_gradient(float x){return (x >= 0) + (x < 0)*(x + 1);}
static inline float relie_gradient(float x){return (x>0) ? 1 : .01;}
static inline float ramp_gradient(float x){return (x>0)+.1;}
static inline float leaky_gradient(float x){return (x>0) ? 1 : .1;}
static inline float tanh_gradient(float x){return 1-x*x;}
static inline float plse_gradient(float x){return (x < 0 || x > 1) ? .01 : .125;}

char *get_activation_string(ACTIVATION a)
{
    switch(a){
        case LOGISTIC:
            return "logistic";
        case LOGGY:
            return "loggy";
        case RELU:
            return "relu";
        case ELU:
            return "elu";
        case RELIE:
            return "relie";
        case RAMP:
            return "ramp";
        case LINEAR:
            return "linear";
        case TANH:
            return "tanh";
        case PLSE:
            return "plse";
        case LEAKY:
            return "leaky";
        case STAIR:
            return "stair";
        case HARDTAN:
            return "hardtan";
        case LHTAN:
            return "lhtan";
        default:
            break;
    }
    return "relu";
}

ACTIVATION get_activation(char *s)
{
    if (strcmp(s, "logistic")==0) return LOGISTIC;
    if (strcmp(s, "loggy")==0) return LOGGY;
    if (strcmp(s, "relu")==0) return RELU;
    if (strcmp(s, "elu")==0) return ELU;
    if (strcmp(s, "relie")==0) return RELIE;
    if (strcmp(s, "plse")==0) return PLSE;
    if (strcmp(s, "hardtan")==0) return HARDTAN;
    if (strcmp(s, "lhtan")==0) return LHTAN;
    if (strcmp(s, "linear")==0) return LINEAR;
    if (strcmp(s, "ramp")==0) return RAMP;
    if (strcmp(s, "leaky")==0) return LEAKY;
    if (strcmp(s, "tanh")==0) return TANH;
    if (strcmp(s, "stair")==0) return STAIR;
    fprintf(stderr, "Couldn't find activation function %s, going with ReLU\n", s);
    return RELU;
}

float activate(float x, ACTIVATION a)
{
    switch(a){
        case LINEAR:
            return linear_activate(x);
        case LOGISTIC:
            return logistic_activate(x);
        case LOGGY:
            return loggy_activate(x);
        case RELU:
            return relu_activate(x);
        case ELU:
            return elu_activate(x);
        case RELIE:
            return relie_activate(x);
        case RAMP:
            return ramp_activate(x);
        case LEAKY:
            return leaky_activate(x);
        case TANH:
            return tanh_activate(x);
        case PLSE:
            return plse_activate(x);
        case STAIR:
            return stair_activate(x);
        case HARDTAN:
            return hardtan_activate(x);
        case LHTAN:
            return lhtan_activate(x);
    }
    return 0;
}

void activate_array(float *x, const int n, const ACTIVATION a)
{
    int i;
    for(i = 0; i < n; ++i){
        x[i] = activate(x[i], a);
    }
}

float gradient(float x, ACTIVATION a)
{
    switch(a){
        case LINEAR:
            return linear_gradient(x);
        case LOGISTIC:
            return logistic_gradient(x);
        case LOGGY:
            return loggy_gradient(x);
        case RELU:
            return relu_gradient(x);
        case ELU:
            return elu_gradient(x);
        case RELIE:
            return relie_gradient(x);
        case RAMP:
            return ramp_gradient(x);
        case LEAKY:
            return leaky_gradient(x);
        case TANH:
            return tanh_gradient(x);
        case PLSE:
            return plse_gradient(x);
        case STAIR:
            return stair_gradient(x);
        case HARDTAN:
            return hardtan_gradient(x);
        case LHTAN:
            return lhtan_gradient(x);
    }
    return 0;
}

///////////////////activation end

void copy_cpu(int N, float *X, int INCX, float *Y, int INCY)
{
    int i;
    for(i = 0; i < N; ++i) Y[i*INCY] = X[i*INCX];
}

void fill_cpu(int N, float ALPHA, float *X, int INCX)
{
    int i;
    for(i = 0; i < N; ++i) X[i*INCX] = ALPHA;
}

void shortcut_cpu(int batch, int w1, int h1, int c1, float *add, int w2, int h2, int c2, float s1, float s2, float *out)
{
    int stride = w1/w2;
    int sample = w2/w1;
    assert(stride == h1/h2);
    assert(sample == h2/h1);
	//printf("shorcut_layer batch=%d,stride=%d,sample=%d\n",batch,stride,sample);
	if(stride < 1) stride = 1;
    if(sample < 1) sample = 1;
    int minw = (w1 < w2) ? w1 : w2;
    int minh = (h1 < h2) ? h1 : h2;
    int minc = (c1 < c2) ? c1 : c2;

    int i,j,k,b;
    for(b = 0; b < batch; ++b){
        for(k = 0; k < minc; ++k){
            for(j = 0; j < minh; ++j){
                for(i = 0; i < minw; ++i){
                    int out_index = i*sample + w2*(j*sample + h2*(k + c2*b));
                    int add_index = i*stride + w1*(j*stride + h1*(k + c1*b));
                    out[out_index] = s1*out[out_index] + s2*add[add_index];
                }
            }
        }
    }
}

void forward_shortcut_layer(const layer l, network net)
{
    //copy_cpu(l.outputs*l.batch, net.input, 1, l.output, 1);
    //shortcut_cpu(l.batch, l.w, l.h, l.c, net.layers[l.index].output, l.out_w, l.out_h, l.out_c, l.alpha, l.beta, l.output);
    //activate_array(l.output, l.outputs*l.batch, l.activation);

    int w = l.w;
    int h = l.h;
    int c = l.c;
	float *add = net.layers[l.index].output;
	float *out = l.output;
	float *in = net.input;

    int i,j,k;
    for(k = 0; k < c; ++k){
        for(j = 0; j < h; ++j){
            for(i = 0; i < w; ++i){
                int index = i + w*(j + h*k );
                out[index] = in[index] + add[index];
            }
        }
    }

}

layer make_shortcut_layer(int batch, int index, int w, int h, int c, int w2, int h2, int c2)
{
    fprintf(stderr, "res  %3d                %4d x%4d x%4d   ->  %4d x%4d x%4d\n",index, w2,h2,c2, w,h,c);
    layer l;
	memset(&l,0,sizeof(layer));

    l.type = SHORTCUT;
    l.batch = batch;
    l.w = w2;
    l.h = h2;
    l.c = c2;
    l.out_w = w;
    l.out_h = h;
    l.out_c = c;
    l.outputs = w*h*c;
    l.inputs = l.outputs;

    l.index = index;

    l.output = (float *)calloc(l.outputs*batch, sizeof(float));;

    l.forward = forward_shortcut_layer;

    return l;
}

int convolutional_out_height(layer l)
{
    return (l.h + 2*l.pad - l.size) / l.stride + 1;
}

int convolutional_out_width(layer l)
{
    return (l.w + 2*l.pad - l.size) / l.stride + 1;
}

static size_t get_workspace_size(layer l){

    return (size_t)l.out_h*l.out_w*l.size*l.size*l.c/l.groups*sizeof(float);
}

void add_bias(float *output, float *biases, int batch, int n, int size)
{
    int i,j,b;
    for(b = 0; b < batch; ++b){
        for(i = 0; i < n; ++i){
            for(j = 0; j < size; ++j){
                output[(b*n + i)*size + j] += biases[i];
            }
        }
    }
}

void scale_bias(float *output, float *scales, int batch, int n, int size)
{
    int i,j,b;
    for(b = 0; b < batch; ++b){
        for(i = 0; i < n; ++i){
            for(j = 0; j < size; ++j){
                output[(b*n + i)*size + j] *= scales[i];
            }
        }
    }
}

float im2col_get_pixel(float *im, int height, int width, int channels,
                        int row, int col, int channel, int pad)
{
    row -= pad;
    col -= pad;

    if (row < 0 || col < 0 ||
        row >= height || col >= width) return 0;
    return im[col + width*(row + height*channel)];
}

//From Berkeley Vision's Caffe!
//https://github.com/BVLC/caffe/blob/master/LICENSE
void im2col_cpu(float* data_im,
     int channels,  int height,  int width,
     int ksize,  int stride, int pad, float* data_col) 
{
    int c,h,w;
    int height_col = (height + 2*pad - ksize) / stride + 1;
    int width_col = (width + 2*pad - ksize) / stride + 1;

    int channels_col = channels * ksize * ksize;
    for (c = 0; c < channels_col; ++c) {
        int w_offset = c % ksize;
        int h_offset = (c / ksize) % ksize;
        int c_im = c / ksize / ksize;
        for (h = 0; h < height_col; ++h) {
            for (w = 0; w < width_col; ++w) {
                int im_row = h_offset + h * stride;
                int im_col = w_offset + w * stride;
                int col_index = (c * height_col + h) * width_col + w;
                data_col[col_index] = im2col_get_pixel(data_im, height, width, channels,
                        im_row, im_col, c_im, pad);
            }
        }
    }
}

void gemm_nn(int M, int N, int K, float ALPHA, 
        float *A, int lda, 
        float *B, int ldb,
        float *C, int ldc)
{
    int i,j,k;
    #pragma omp parallel for
    for(i = 0; i < M; ++i){
        for(k = 0; k < K; ++k){
            register float A_PART = ALPHA*A[i*lda+k];
            for(j = 0; j < N; ++j){
                C[i*ldc+j] += A_PART*B[k*ldb+j];
            }
        }
    }
}

void gemm_cpu(int TA, int TB, int M, int N, int K, float ALPHA, 
        float *A, int lda, 
        float *B, int ldb,
        float BETA,
        float *C, int ldc)
{
    //printf("cpu: %d %d %d %d %d %f %d %d %f %d\n",TA, TB, M, N, K, ALPHA, lda, ldb, BETA, ldc);
    int i, j;
    for(i = 0; i < M; ++i){
        for(j = 0; j < N; ++j){
            C[i*ldc + j] *= BETA;
        }
    }
    if(!TA && !TB)
        gemm_nn(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
    //else if(TA && !TB)
    //    gemm_tn(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
    //else if(!TA && TB)
    //    gemm_nt(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
    //else
    //    gemm_tt(M, N, K, ALPHA,A,lda, B, ldb,C,ldc);
}

void gemm(int TA, int TB, int M, int N, int K, float ALPHA, 
        float *A, int lda, 
        float *B, int ldb,
        float BETA,
        float *C, int ldc)
{
    gemm_cpu( TA,  TB,  M, N, K, ALPHA,A,lda, B, ldb,BETA,C,ldc);
}

void normalize_cpu(float *x, float *mean, float *variance, int batch, int filters, int spatial)
{
    int b, f, i;
    for(b = 0; b < batch; ++b){
        for(f = 0; f < filters; ++f){
            for(i = 0; i < spatial; ++i){
                int index = b*filters*spatial + f*spatial + i;
                x[index] = (x[index] - mean[f])/(sqrt(variance[f]) + .000001f);
            }
        }
    }
}

void forward_batchnorm_layer(layer l, network net)//for conv
{
    normalize_cpu(l.output, l.rolling_mean, l.rolling_variance, l.batch, l.out_c, l.out_h*l.out_w);   
    scale_bias(l.output, l.scales, l.batch, l.out_c, l.out_h*l.out_w);
    add_bias(l.output, l.biases, l.batch, l.out_c, l.out_h*l.out_w);
}

void CONV_Padding_Relu(float *Input,float *Output,float *Weight,const int InFM_num,const int OutFM_num,const int Kernel_size,const int Kernel_stride,const int Input_w,const int Input_h,const int Padding)
{
	// (output_w - 1)*Kernel_stride + Kernel_size = Input_w
	const int output_w = (Input_w - Kernel_size + 2*Padding)/Kernel_stride + 1 ;
	const int output_h = (Input_h - Kernel_size + 2*Padding)/Kernel_stride + 1 ;
	int x, y, of, inf;
	int m,n;
    for( of = 0; of < OutFM_num; of++){
    	for( y = 0; y < output_h; y++) {
    		for( x = 0; x < output_w; x++){
				float tmp = 0.0;
				for(inf = 0;inf < InFM_num; inf++)
				{
					int intput_offset = inf*Input_w*Input_h + (y*Kernel_stride - Padding)*Input_w + x*Kernel_stride - Padding;
					for(m = 0;m < Kernel_size; m++)
					{
    					for(n = 0;n < Kernel_size; n++)
						{
							int kernel_offset = of*InFM_num*Kernel_size*Kernel_size + inf*Kernel_size*Kernel_size;
							bool inFM_width  = ((x*Kernel_stride + n - Padding) >= 0)&&((x*Kernel_stride + n - Padding) < Input_w);
							bool inFM_height = ((y*Kernel_stride + m - Padding) >= 0)&&((y*Kernel_stride + m - Padding) < Input_h);
							if(inFM_width&&inFM_height)
								tmp += Weight[kernel_offset + m*Kernel_size + n]*Input[intput_offset + m*Input_w + n];
    					}
    				}
				}
    			Output[of*output_w*output_h + y*output_w + x] = tmp;
    		}
    	}
    }
}

void forward_convolutional_layer(layer l, network net)
{
    int i, j;

    fill_cpu(l.outputs*l.batch, 0, l.output, 1);

	//printf("c=%d,n=%d,size=%d,stride=%d,w=%d,h=%d,pad=%d\n",l.c,l.n,l.size,l.stride,l.w,l.h,l.pad);

    //int m = l.n/l.groups;
    //int k = l.size*l.size*l.c/l.groups;
    //int n = l.out_w*l.out_h;
    //for(i = 0; i < l.batch; ++i){
    //    for(j = 0; j < l.groups; ++j){
    //        float *a = l.weights + j*l.nweights/l.groups;
    //        float *b = net.workspace;
    //        float *c = l.output + (i*l.groups + j)*n*m;

    //        im2col_cpu(net.input + (i*l.groups + j)*l.c/l.groups*l.h*l.w,
    //            l.c/l.groups, l.h, l.w, l.size, l.stride, l.pad, b);
    //        gemm(0,0,m,n,k,1,a,k,b,n,1,c,n);
    //    }
    //}

    int m = l.n;
    int k = l.size*l.size*l.c;
    int n = l.out_w*l.out_h;
    float *a = l.weights;
    float *b = net.workspace;
    float *c = l.output;

    im2col_cpu(net.input,l.c, l.h, l.w, l.size, l.stride, l.pad, b);
    gemm(0,0,m,n,k,1,a,k,b,n,1,c,n);

    //CONV_Padding_Relu(net.input,l.output,l.weights,l.c,l.n,l.size,l.stride,l.w,l.h,l.pad);

    if(l.batch_normalize){
        forward_batchnorm_layer(l, net);
    } else {
        add_bias(l.output, l.biases, l.batch, l.n, l.out_h*l.out_w);
    }

    activate_array(l.output, l.outputs*l.batch, l.activation);
}

layer make_convolutional_layer(int batch, int h, int w, int c, int n, int groups, int size, int stride, int padding, ACTIVATION activation, int batch_normalize, int binary, int xnor, int adam)
{
    int i;
	layer l;
    memset(&l,0,sizeof(layer));
	l.type = CONVOLUTIONAL;

    l.groups = groups;
    l.h = h;
    l.w = w;
    l.c = c;
    l.n = n;
    l.binary = binary;
    l.xnor = xnor;
    l.batch = batch;
    l.stride = stride;
    l.size = size;
    l.pad = padding;
    l.batch_normalize = batch_normalize;

 //   l.weights = (float *)calloc(c/groups*n*size*size, sizeof(float));
  //  l.biases = (float *)calloc(n, sizeof(float));

    l.nweights = c/groups*n*size*size;
    l.nbiases = n;

	int out_w = convolutional_out_width(l);
    int out_h = convolutional_out_height(l);
    l.out_h = out_h;
    l.out_w = out_w;
    l.out_c = n;
    l.outputs = l.out_h * l.out_w * l.out_c;
    l.inputs = l.w * l.h * l.c;

   // l.output = (float *)calloc(l.batch*l.outputs, sizeof(float));
    l.forward = forward_convolutional_layer;

    if(batch_normalize){
    //    l.scales = (float *)calloc(n, sizeof(float));
    //   l.rolling_mean = (float *)calloc(n, sizeof(float));
//l.rolling_variance = (float *)calloc(n, sizeof(float));
    }

    l.workspace_size = get_workspace_size(l);
    l.activation = activation;

    fprintf(stderr, "conv  %5d %2d x%2d /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d  %5.3f BFLOPs\n", n, size, size, stride, w, h, c, l.out_w, l.out_h, l.out_c, (2.0 * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w)/1000000000.);

    return l;
}

void upsample_cpu(float *in, int w, int h, int c, int batch, int stride, int forward, float scale, float *out)
{
    int i, j, k, b;
    for(b = 0; b < batch; ++b){
        for(k = 0; k < c; ++k){
            for(j = 0; j < h*stride; ++j){
                for(i = 0; i < w*stride; ++i){
                    int in_index = b*w*h*c + k*w*h + (j/stride)*w + i/stride;
                    int out_index = b*w*h*c*stride*stride + k*w*h*stride*stride + j*w*stride + i;
                    if(forward) out[out_index] = scale*in[in_index];
                    else in[in_index] += scale*out[out_index];
                }
            }
        }
    }
}

void forward_upsample_layer(const layer l, network net)
{
    //fill_cpu(l.outputs*l.batch, 0, l.output, 1);
    //upsample_cpu(net.input, l.w, l.h, l.c, l.batch, l.stride, 1, l.scale, l.output);

	int c = l.c;
	int h = l.h;
	int w = l.w;
	int stride = l.stride;
	float *in = net.input;
	float *out = l.output;

    int i, j, k;

    for(k = 0; k < c; ++k){
        for(j = 0; j < h*stride; ++j){
            for(i = 0; i < w*stride; ++i){
                int in_index = k*w*h + (j/stride)*w + i/stride;
                int out_index = k*w*h*stride*stride + j*w*stride + i;
                out[out_index] = in[in_index];

            }
        }
    }

}

layer make_upsample_layer(int batch, int w, int h, int c, int stride)
{
    layer l;
	memset(&l,0,sizeof(layer));

    l.type = UPSAMPLE;
    l.batch = batch;
    l.w = w;
    l.h = h;
    l.c = c;
    l.out_w = w*stride;
    l.out_h = h*stride;
    l.out_c = c;
    if(stride < 0){
        stride = -stride;
        l.reverse=1;
        l.out_w = w/stride;
        l.out_h = h/stride;
    }
    l.stride = stride;
    l.outputs = l.out_w*l.out_h*l.out_c;
    l.inputs = l.w*l.h*l.c;
    l.output = (float *)calloc(l.outputs*batch, sizeof(float));;

    l.forward = forward_upsample_layer;
    
    if(l.reverse) fprintf(stderr, "downsample         %2dx  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", stride, w, h, c, l.out_w, l.out_h, l.out_c);
    else fprintf(stderr, "upsample           %2dx  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", stride, w, h, c, l.out_w, l.out_h, l.out_c);
    return l;
}

void forward_route_layer(const layer l, network net)
{
    int i, j;
    int offset = 0;
    for(i = 0; i < l.n; ++i){
        int index = l.input_layers[i];
        float *input = net.layers[index].output;
        int input_size = l.input_sizes[i];
		copy_cpu(input_size, input, 1, l.output + offset, 1);
        offset += input_size;
    }
}

layer make_route_layer(int batch, int n, int *input_layers, int *input_sizes)
{
    fprintf(stderr,"route ");
    layer l;
	memset(&l,0,sizeof(layer));

    l.type = ROUTE;
    l.batch = batch;
    l.n = n;
    l.input_layers = input_layers;
    l.input_sizes = input_sizes;
    int i;
    int outputs = 0;
    for(i = 0; i < n; ++i){
        fprintf(stderr," %d", input_layers[i]);
        outputs += input_sizes[i];
    }
    fprintf(stderr, "\n");
    l.outputs = outputs;
    l.inputs = outputs;

  //  l.output = (float *)calloc(outputs*batch, sizeof(float));;
    l.forward = forward_route_layer;

    return l;
}

static int entry_index(layer l, int batch, int location, int entry)
{
    int n =   location / (l.w*l.h);
    int loc = location % (l.w*l.h);
    return batch*l.outputs + n*l.w*l.h*(4+l.classes+1) + entry*l.w*l.h + loc;
}

void forward_yolo_layer(const layer l, network net)
{
    int i,j,b,t,n;

	//char line[256];
	//FILE *fp3;
	//char filename[256];
	//sprintf(filename, "yolo_layer_%d.txt", l.outputs);
	//printf("YOLO_layer:outputs=%d,%s\n",l.outputs,filename);
 //   if( (fp3 = fopen(filename, "w")) == NULL)fprintf(stderr,"CANNOT OPEN\n");
	//int x;
 //   for( x = 0; x < l.outputs; x++)
	//{
	//	sprintf(line, "%f\n", net.input[x]);
	//	if(fputs(line,fp3)<0)fprintf(stderr,"write FILE failed\n");
 //   }
 //   fclose(fp3);

    memcpy(l.output, net.input, l.outputs*l.batch*sizeof(float));

    for (b = 0; b < l.batch; ++b){
        for(n = 0; n < l.n; ++n){
            int index = entry_index(l, b, n*l.w*l.h, 0);
            activate_array(l.output + index, 2*l.w*l.h, LOGISTIC);
            index = entry_index(l, b, n*l.w*l.h, 4);
            activate_array(l.output + index, (1+l.classes)*l.w*l.h, LOGISTIC);
        }
    }

	return ;

}


layer make_yolo_layer(int batch, int w, int h, int n, int total, int *mask, int classes)
{
    int i;
    layer l;
	memset(&l,0,sizeof(layer));

    l.type = YOLO;

    l.n = n;
    l.total = total;
    l.batch = batch;
    l.h = h;
    l.w = w;
    l.c = n*(classes + 4 + 1);
    l.out_w = l.w;
    l.out_h = l.h;
    l.out_c = l.c;
    l.classes = classes;
    //l.cost = (float *)calloc(1, sizeof(float));
    l.biases = (float *)calloc(total*2, sizeof(float));
    if(mask) l.mask = mask;
    else{
        l.mask = (int *)calloc(n, sizeof(int));
        for(i = 0; i < n; ++i){
            l.mask[i] = i;
        }
    }
    //l.bias_updates = (float *)calloc(n*2, sizeof(float));
    l.outputs = h*w*n*(classes + 4 + 1);
    l.inputs = l.outputs;
    //l.truths = 90*(4 + 1);
    //l.delta = (float *)calloc(batch*l.outputs, sizeof(float));
    l.output = (float *)calloc(batch*l.outputs, sizeof(float));
    for(i = 0; i < total*2; ++i){
        l.biases[i] = .5;
    }

    l.forward = forward_yolo_layer;

    fprintf(stderr, "detection\n");
    srand(0);

    return l;
}

/////////////////praser begin
typedef struct{
    char *type;
    list *options;
}section;

list *read_cfg(char *filename);

LAYER_TYPE string_to_layer_type(char * type)
{

    if (strcmp(type, "[shortcut]")==0) return SHORTCUT;
    if (strcmp(type, "[crop]")==0) return CROP;
    if (strcmp(type, "[cost]")==0) return COST;
    if (strcmp(type, "[detection]")==0) return DETECTION;
    if (strcmp(type, "[region]")==0) return REGION;
    if (strcmp(type, "[yolo]")==0) return YOLO;
    if (strcmp(type, "[local]")==0) return LOCAL;
    if (strcmp(type, "[conv]")==0
            || strcmp(type, "[convolutional]")==0) return CONVOLUTIONAL;
    if (strcmp(type, "[deconv]")==0
            || strcmp(type, "[deconvolutional]")==0) return DECONVOLUTIONAL;
    if (strcmp(type, "[activation]")==0) return ACTIVE;
    if (strcmp(type, "[logistic]")==0) return LOGXENT;
    if (strcmp(type, "[l2norm]")==0) return L2NORM;
    if (strcmp(type, "[net]")==0
            || strcmp(type, "[network]")==0) return NETWORK;
    if (strcmp(type, "[crnn]")==0) return CRNN;
    if (strcmp(type, "[gru]")==0) return GRU;
    if (strcmp(type, "[lstm]") == 0) return LSTM;
    if (strcmp(type, "[rnn]")==0) return RNN;
    if (strcmp(type, "[conn]")==0
            || strcmp(type, "[connected]")==0) return CONNECTED;
    if (strcmp(type, "[max]")==0
            || strcmp(type, "[maxpool]")==0) return MAXPOOL;
    if (strcmp(type, "[reorg]")==0) return REORG;
    if (strcmp(type, "[avg]")==0
            || strcmp(type, "[avgpool]")==0) return AVGPOOL;
    if (strcmp(type, "[dropout]")==0) return DROPOUT;
    if (strcmp(type, "[lrn]")==0
            || strcmp(type, "[normalization]")==0) return NORMALIZATION;
    if (strcmp(type, "[batchnorm]")==0) return BATCHNORM;
    if (strcmp(type, "[soft]")==0
            || strcmp(type, "[softmax]")==0) return SOFTMAX;
    if (strcmp(type, "[route]")==0) return ROUTE;
    if (strcmp(type, "[upsample]")==0) return UPSAMPLE;
    return BLANK;
}

void free_section(section *s)
{
    free(s->type);
    node *n = s->options->front;
    while(n){
        kvp *pair = (kvp *)n->val;
        free(pair->key);
        free(pair);
        node *next = n->next;
        free(n);
        n = next;
    }
    free(s->options);
    free(s);
}

void parse_data(char *data, float *a, int n)
{
    int i;
    if(!data) return;
    char *curr = data;
    char *next = data;
    int done = 0;
    for(i = 0; i < n && !done; ++i){
        while(*++next !='\0' && *next != ',');
        if(*next == '\0') done = 1;
        *next = '\0';
        sscanf(curr, "%g", &a[i]);
        curr = next+1;
    }
}

typedef struct size_params{
    int batch;
    int inputs;
    int h;
    int w;
    int c;
    int index;
    int time_steps;
    network *net;
} size_params;

layer parse_convolutional(list *options, size_params params)
{
    int n = option_find_int(options, "filters",1);
    int size = option_find_int(options, "size",1);
    int stride = option_find_int(options, "stride",1);
    int pad = option_find_int_quiet(options, "pad",0);
    int padding = option_find_int_quiet(options, "padding",0);
    int groups = option_find_int_quiet(options, "groups", 1);
    if(pad) padding = size/2;

    char *activation_s = option_find_str(options, "activation", "logistic");
    ACTIVATION activation = get_activation(activation_s);

    int batch,h,w,c;
    h = params.h;
    w = params.w;
    c = params.c;
    batch=params.batch;
    if(!(h && w && c)) error("Layer before convolutional layer must output image.");
    int batch_normalize = option_find_int_quiet(options, "batch_normalize", 0);
    int binary = option_find_int_quiet(options, "binary", 0);
    int xnor = option_find_int_quiet(options, "xnor", 0);

    layer l = make_convolutional_layer(batch,h,w,c,n,groups,size,stride,padding,activation, batch_normalize, binary, xnor, params.net->adam);
    l.flipped = option_find_int_quiet(options, "flipped", 0);
    l.dot = option_find_float_quiet(options, "dot", 0);

    return l;
}

int *parse_yolo_mask(char *a, int *num)
{
    int *mask = 0;
    if(a){
        int len = strlen(a);
        int n = 1;
        int i;
        for(i = 0; i < len; ++i){
            if (a[i] == ',') ++n;
        }
        mask = (int *)calloc(n, sizeof(int));
        for(i = 0; i < n; ++i){
            int val = atoi(a);
            mask[i] = val;
            a = strchr(a, ',')+1;
        }
        *num = n;
    }
    return mask;
}

layer parse_yolo(list *options, size_params params)
{
    int classes = option_find_int(options, "classes", 20);
    int total = option_find_int(options, "num", 1);
    int num = total;

    char *a = option_find_str(options, "mask", 0);
    int *mask = parse_yolo_mask(a, &num);
    layer l = make_yolo_layer(params.batch, params.w, params.h, num, total, mask, classes);
    assert(l.outputs == params.inputs);

    l.max_boxes = option_find_int_quiet(options, "max",90);
    l.jitter = option_find_float(options, "jitter", .2);

    l.ignore_thresh = option_find_float(options, "ignore_thresh", .5);
    l.truth_thresh = option_find_float(options, "truth_thresh", 1);
    l.random = option_find_int_quiet(options, "random", 0);

    a = option_find_str(options, "anchors", 0);
    if(a){
        int len = strlen(a);
        int n = 1;
        int i;
        for(i = 0; i < len; ++i){
            if (a[i] == ',') ++n;
        }
        for(i = 0; i < n; ++i){
            float bias = atof(a);
            l.biases[i] = bias;
            a = strchr(a, ',')+1;
        }
    }
    return l;
}

layer parse_shortcut(list *options, size_params params, network *net)
{
    char *l = option_find(options, "from");
    int index = atoi(l);
    if(index < 0) index = params.index + index;

    int batch = params.batch;
    layer from = net->layers[index];

    layer s = make_shortcut_layer(batch, index, params.w, params.h, params.c, from.out_w, from.out_h, from.out_c);

    char *activation_s = option_find_str(options, "activation", "linear");
    ACTIVATION activation = get_activation(activation_s);
    s.activation = activation;
    s.alpha = option_find_float_quiet(options, "alpha", 1);
    s.beta = option_find_float_quiet(options, "beta", 1);
    return s;
}

layer parse_upsample(list *options, size_params params, network *net)
{

    int stride = option_find_int(options, "stride",2);
    layer l = make_upsample_layer(params.batch, params.w, params.h, params.c, stride);
    l.scale = option_find_float_quiet(options, "scale", 1);
    return l;
}

layer parse_route(list *options, size_params params, network *net)
{
    char *l = option_find(options, "layers");
    int len = strlen(l);
    if(!l) error("Route Layer must specify input layers");
    int n = 1;
    int i;
    for(i = 0; i < len; ++i){
        if (l[i] == ',') ++n;
    }

    int *layers = (int *)calloc(n, sizeof(int));
    int *sizes = (int *)calloc(n, sizeof(int));
    for(i = 0; i < n; ++i){
        int index = atoi(l);
        l = strchr(l, ',')+1;
        if(index < 0) index = params.index + index;
        layers[i] = index;
        sizes[i] = net->layers[index].outputs;
    }
    int batch = params.batch;

    layer route_layer = make_route_layer(batch, n, layers, sizes);

    layer first = net->layers[layers[0]];
    route_layer.out_w = first.out_w;
    route_layer.out_h = first.out_h;
    route_layer.out_c = first.out_c;
    for(i = 1; i < n; ++i){
        int index = layers[i];
        layer next = net->layers[index];
        if(next.out_w == first.out_w && next.out_h == first.out_h){
            route_layer.out_c += next.out_c;
        }else{
            route_layer.out_h = route_layer.out_w = route_layer.out_c = 0;
        }
    }

    return route_layer;
}

void softmax(float *input, int n, float temp, int stride, float *output)
{
    int i;
    float sum = 0;
    float largest = -FLT_MAX;
    for(i = 0; i < n; ++i){
        if(input[i*stride] > largest) largest = input[i*stride];
    }
    for(i = 0; i < n; ++i){
        float e = exp(input[i*stride]/temp - largest/temp);
        sum += e;
        output[i*stride] = e;
    }
    for(i = 0; i < n; ++i){
        output[i*stride] /= sum;
    }
}

void softmax_cpu(float *input, int n, int batch, int batch_offset, int groups, int group_offset, int stride, float temp, float *output)
{
    int g, b;
    for(b = 0; b < batch; ++b){
        for(g = 0; g < groups; ++g){
            softmax(input + b*batch_offset + g*group_offset, n, temp, stride, output + b*batch_offset + g*group_offset);
        }
    }
}

void forward_region_layer(const layer l, network net)
{
    int i,j,b,t,n;
    memcpy(l.output, net.input, l.outputs*l.batch*sizeof(float));

#ifndef GPU
    for (b = 0; b < l.batch; ++b){
        for(n = 0; n < l.n; ++n){
            int index = entry_index(l, b, n*l.w*l.h, 0);
            activate_array(l.output + index, 2*l.w*l.h, LOGISTIC);
            index = entry_index(l, b, n*l.w*l.h, l.coords);
            if(!l.background) activate_array(l.output + index,   l.w*l.h, LOGISTIC);
            index = entry_index(l, b, n*l.w*l.h, l.coords + 1);
            //if(!l.softmax) activate_array(l.output + index, l.classes*l.w*l.h, LOGISTIC);
        }
    }

	if (l.softmax){
        int index = entry_index(l, 0, 0, l.coords + !l.background);
        softmax_cpu(net.input + index, l.classes + l.background, l.batch*l.n, l.inputs/l.n, l.w*l.h, 1, l.w*l.h, 1, l.output + index);
    }

	char line[256];
	FILE *fp3;
	char filename[256];
	sprintf(filename, "yolo_layer_%d.txt", 123123);
	printf("YOLO_layer:outputs=%d,%s\n",l.outputs,filename);
    if( (fp3 = fopen(filename, "w")) == NULL)fprintf(stderr,"CANNOT OPEN\n");
	int x;
    for( x = 0; x < l.outputs; x++)
	{
		sprintf(line, "%f\n", net.input[x]);
		if(fputs(line,fp3)<0)fprintf(stderr,"write FILE failed\n");
    }
    fclose(fp3);

#endif

    if(!net.train) return;
}

layer make_region_layer(int batch, int w, int h, int n, int classes, int coords)
{
    layer l;
	memset(&l,0,sizeof(layer));
    l.type = REGION;

    l.n = n;
    l.batch = batch;
    l.h = h;
    l.w = w;
    l.c = n*(classes + coords + 1);
    l.out_w = l.w;
    l.out_h = l.h;
    l.out_c = l.c;
    l.classes = classes;
    l.coords = coords;
    l.biases = (float *)calloc(n*2, sizeof(float));
    l.outputs = h*w*n*(classes + coords + 1);
    l.inputs = l.outputs;
    l.truths = 30*(l.coords + 1);
    l.output = (float *)calloc(batch*l.outputs, sizeof(float));
    int i;
    for(i = 0; i < n*2; ++i){
        l.biases[i] = .5;
    }

    l.forward = forward_region_layer;

    fprintf(stderr, "detection\n");
    srand(0);

    return l;
}

layer parse_region(list *options, size_params params)
{
    int coords = option_find_int(options, "coords", 4);
    int classes = option_find_int(options, "classes", 20);
    int num = option_find_int(options, "num", 1);

    layer l = make_region_layer(params.batch, params.w, params.h, num, classes, coords);
    assert(l.outputs == params.inputs);

    l.log = option_find_int_quiet(options, "log", 0);
    l.sqrt = option_find_int_quiet(options, "sqrt", 0);

    l.softmax = option_find_int(options, "softmax", 0);
    l.background = option_find_int_quiet(options, "background", 0);
    l.max_boxes = option_find_int_quiet(options, "max",30);
    l.jitter = option_find_float(options, "jitter", .2);
    l.rescore = option_find_int_quiet(options, "rescore",0);

    l.thresh = option_find_float(options, "thresh", .5);
    l.classfix = option_find_int_quiet(options, "classfix", 0);
    l.absolute = option_find_int_quiet(options, "absolute", 0);
    l.random = option_find_int_quiet(options, "random", 0);

    l.coord_scale = option_find_float(options, "coord_scale", 1);
    l.object_scale = option_find_float(options, "object_scale", 1);
    l.noobject_scale = option_find_float(options, "noobject_scale", 1);
    l.mask_scale = option_find_float(options, "mask_scale", 1);
    l.class_scale = option_find_float(options, "class_scale", 1);
    l.bias_match = option_find_int_quiet(options, "bias_match",0);

    char *tree_file = option_find_str(options, "tree", 0);
   // if (tree_file) l.softmax_tree = read_tree(tree_file);
    char *map_file = option_find_str(options, "map", 0);
   // if (map_file) l.map = read_map(map_file);

    char *a = option_find_str(options, "anchors", 0);
    if(a){
        int len = strlen(a);
        int n = 1;
        int i;
        for(i = 0; i < len; ++i){
            if (a[i] == ',') ++n;
        }
        for(i = 0; i < n; ++i){
            float bias = atof(a);
            l.biases[i] = bias;
            a = strchr(a, ',')+1;
        }
    }
    return l;
}

void reorg_cpu(float *x, int w, int h, int c, int batch, int stride, int forward, float *out)
{
    int b,i,j,k;
    int out_c = c/(stride*stride);

    for(b = 0; b < batch; ++b){
        for(k = 0; k < c; ++k){
            for(j = 0; j < h; ++j){
                for(i = 0; i < w; ++i){
                    int in_index  = i + w*(j + h*(k + c*b));
                    int c2 = k % out_c;
                    int offset = k / out_c;
                    int w2 = i*stride + offset % stride;
                    int h2 = j*stride + offset / stride;
                    int out_index = w2 + w*stride*(h2 + h*stride*(c2 + out_c*b));
                    if(forward) out[out_index] = x[in_index];
                    else out[in_index] = x[out_index];
                }
            }
        }
    }
}

void forward_reorg_layer(const layer l, network net)
{
    int i;
    //if(l.flatten){
    //    memcpy(l.output, net.input, l.outputs*l.batch*sizeof(float));
    //    if(l.reverse){
    //        flatten(l.output, l.w*l.h, l.c, l.batch, 0);
    //    }else{
    //        flatten(l.output, l.w*l.h, l.c, l.batch, 1);
    //    }
    //} else if (l.extra) {
    //    for(i = 0; i < l.batch; ++i){
    //        copy_cpu(l.inputs, net.input + i*l.inputs, 1, l.output + i*l.outputs, 1);
    //    }
    //} else if (l.reverse){
    //    reorg_cpu(net.input, l.w, l.h, l.c, l.batch, l.stride, 1, l.output);
    //} else {
        reorg_cpu(net.input, l.w, l.h, l.c, l.batch, l.stride, 0, l.output);
    //}
}

layer make_reorg_layer(int batch, int w, int h, int c, int stride, int reverse, int flatten, int extra)
{
    layer l;
	memset(&l,0,sizeof(layer));

    l.type = REORG;
    l.batch = batch;
    l.stride = stride;
    l.extra = extra;
    l.h = h;
    l.w = w;
    l.c = c;
    l.flatten = flatten;
    if(reverse){
        l.out_w = w*stride;
        l.out_h = h*stride;
        l.out_c = c/(stride*stride);
    }else{
        l.out_w = w/stride;
        l.out_h = h/stride;
        l.out_c = c*(stride*stride);
    }
    l.reverse = reverse;

    l.outputs = l.out_h * l.out_w * l.out_c;
    l.inputs = h*w*c;
    if(l.extra){
        l.out_w = l.out_h = l.out_c = 0;
        l.outputs = l.inputs + l.extra;
    }

    if(extra){
        fprintf(stderr, "reorg              %4d   ->  %4d\n",  l.inputs, l.outputs);
    } else {
        fprintf(stderr, "reorg              /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n",  stride, w, h, c, l.out_w, l.out_h, l.out_c);
    }
    int output_size = l.outputs * batch;
    //l.output =  (float *)calloc(output_size, sizeof(float));

    l.forward = forward_reorg_layer;


    return l;
}

layer parse_reorg(list *options, size_params params)
{
    int stride = option_find_int(options, "stride",1);
    int reverse = option_find_int_quiet(options, "reverse",0);
    int flatten = option_find_int_quiet(options, "flatten",0);
    int extra = option_find_int_quiet(options, "extra",0);

    int batch,h,w,c;
    h = params.h;
    w = params.w;
    c = params.c;
    batch=params.batch;
    if(!(h && w && c)) error("Layer before reorg layer must output image.");

    layer layer = make_reorg_layer(batch,w,h,c,stride,reverse, flatten, extra);
    return layer;
}

void forward_maxpool_layer(layer l, network net)
{
    int b,i,j,k,m,n;
    int w_offset = -l.pad;
    int h_offset = -l.pad;

    int h = l.out_h;
    int w = l.out_w;
    int c = l.c;

    for(b = 0; b < l.batch; ++b){
        for(k = 0; k < c; ++k){
            for(i = 0; i < h; ++i){
                for(j = 0; j < w; ++j){
                    int out_index = j + w*(i + h*(k + c*b));
                    float max = -FLT_MAX;
                    int max_i = -1;
                    for(n = 0; n < l.size; ++n){
                        for(m = 0; m < l.size; ++m){
                            int cur_h = h_offset + i*l.stride + n;
                            int cur_w = w_offset + j*l.stride + m;
                            int index = cur_w + l.w*(cur_h + l.h*(k + b*l.c));
                            int valid = (cur_h >= 0 && cur_h < l.h &&
                                         cur_w >= 0 && cur_w < l.w);
                            float val = (valid != 0) ? net.input[index] : -FLT_MAX;
                            max_i = (val > max) ? index : max_i;
                            max   = (val > max) ? val   : max;
                        }
                    }
                    l.output[out_index] = max;
                    l.indexes[out_index] = max_i;
                }
            }
        }
    }
}

//layer make_maxpool_layer(int batch, int h, int w, int c, int size, int stride, int padding)
//{
//    layer l;
//	memset(&l,0,sizeof(layer));
//    l.type = MAXPOOL;
//    l.batch = batch;
//    l.h = h;
//    l.w = w;
//    l.c = c;
//    l.pad = padding;
//    l.out_w = (w + 2*padding)/stride;
//    l.out_h = (h + 2*padding)/stride;
//    l.out_c = c;
//    l.outputs = l.out_h * l.out_w * l.out_c;
//    l.inputs = h*w*c;
//    l.size = size;
//    l.stride = stride;
//    int output_size = l.out_h * l.out_w * l.out_c * batch;
//    //l.indexes = (int *)calloc(output_size, sizeof(int));
//    //l.output =  (float *)calloc(output_size, sizeof(float));
//    l.forward = forward_maxpool_layer;
//
//    fprintf(stderr, "max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", size, size, stride, w, h, c, l.out_w, l.out_h, l.out_c);
//    return l;
//}

layer make_maxpool_layer(int batch, int h, int w, int c, int size, int stride, int padding)
{
    layer l;
	memset(&l,0,sizeof(layer));
    l.type = MAXPOOL;
    l.batch = batch;
    l.h = h;
    l.w = w;
    l.c = c;
    l.pad = padding;
    l.out_w = (w + padding - size)/stride + 1;
    l.out_h = (h + padding - size)/stride + 1;
    l.out_c = c;
    l.outputs = l.out_h * l.out_w * l.out_c;
    l.inputs = h*w*c;
    l.size = size;
    l.stride = stride;
    int output_size = l.out_h * l.out_w * l.out_c * batch;
    //l.indexes = calloc(output_size, sizeof(int));
    //l.output =  calloc(output_size, sizeof(float));
    //l.delta =   calloc(output_size, sizeof(float));
    l.forward = forward_maxpool_layer;
    //l.backward = backward_maxpool_layer;

    fprintf(stderr, "max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", size, size, stride, w, h, c, l.out_w, l.out_h, l.out_c);
    return l;
}


layer parse_maxpool(list *options, size_params params)
{
    int stride = option_find_int(options, "stride",1);
    int size = option_find_int(options, "size",stride);
    int padding = option_find_int_quiet(options, "padding", size-1);

    int batch,h,w,c;
    h = params.h;
    w = params.w;
    c = params.c;
    batch=params.batch;
    if(!(h && w && c)) error("Layer before maxpool layer must output image.");

    layer maxpool_layer = make_maxpool_layer(batch,h,w,c,size,stride,padding);
    return maxpool_layer;
}

learning_rate_policy get_policy(char *s)
{
    if (strcmp(s, "random")==0) return RANDOM;
    if (strcmp(s, "poly")==0) return POLY;
    if (strcmp(s, "constant")==0) return CONSTANT;
    if (strcmp(s, "step")==0) return STEP;
    if (strcmp(s, "exp")==0) return EXP;
    if (strcmp(s, "sigmoid")==0) return SIG;
    if (strcmp(s, "steps")==0) return STEPS;
    fprintf(stderr, "Couldn't find policy %s, going with constant\n", s);
    return CONSTANT;
}

void parse_net_options(list *options, network *net)
{
    net->batch = option_find_int(options, "batch",1);
    net->learning_rate = option_find_float(options, "learning_rate", .001);
    net->momentum = option_find_float(options, "momentum", .9);
    net->decay = option_find_float(options, "decay", .0001);
    int subdivs = option_find_int(options, "subdivisions",1);
    net->time_steps = option_find_int_quiet(options, "time_steps",1);
    net->notruth = option_find_int_quiet(options, "notruth",0);
    net->batch /= subdivs;
    net->batch *= net->time_steps;
    net->subdivisions = subdivs;
    net->random = option_find_int_quiet(options, "random", 0);

    net->adam = option_find_int_quiet(options, "adam", 0);
    if(net->adam){
        net->B1 = option_find_float(options, "B1", .9);
        net->B2 = option_find_float(options, "B2", .999);
        net->eps = option_find_float(options, "eps", .0000001);
    }

    net->h = option_find_int_quiet(options, "height",0);
    net->w = option_find_int_quiet(options, "width",0);
    net->c = option_find_int_quiet(options, "channels",0);
    net->inputs = option_find_int_quiet(options, "inputs", net->h * net->w * net->c);
    net->max_crop = option_find_int_quiet(options, "max_crop",net->w*2);
    net->min_crop = option_find_int_quiet(options, "min_crop",net->w);
    net->max_ratio = option_find_float_quiet(options, "max_ratio", (float) net->max_crop / net->w);
    net->min_ratio = option_find_float_quiet(options, "min_ratio", (float) net->min_crop / net->w);
    net->center = option_find_int_quiet(options, "center",0);
    net->clip = option_find_float_quiet(options, "clip", 0);

    net->angle = option_find_float_quiet(options, "angle", 0);
    net->aspect = option_find_float_quiet(options, "aspect", 1);
    net->saturation = option_find_float_quiet(options, "saturation", 1);
    net->exposure = option_find_float_quiet(options, "exposure", 1);
    net->hue = option_find_float_quiet(options, "hue", 0);

    if(!net->inputs && !(net->h && net->w && net->c)) error("No input parameters supplied");

    char *policy_s = option_find_str(options, "policy", "constant");
    net->policy = get_policy(policy_s);
    net->burn_in = option_find_int_quiet(options, "burn_in", 0);
    net->power = option_find_float_quiet(options, "power", 4);
    if(net->policy == STEP){
        net->step = option_find_int(options, "step", 1);
        net->scale = option_find_float(options, "scale", 1);
    } else if (net->policy == STEPS){
        char *l = option_find(options, "steps");
        char *p = option_find(options, "scales");
        if(!l || !p) error("STEPS policy must have steps and scales in cfg file");

        int len = strlen(l);
        int n = 1;
        int i;
        for(i = 0; i < len; ++i){
            if (l[i] == ',') ++n;
        }
        int *steps = (int *)calloc(n, sizeof(int));
        float *scales = (float *)calloc(n, sizeof(float));
        for(i = 0; i < n; ++i){
            int step    = atoi(l);
            float scale = atof(p);
            l = strchr(l, ',')+1;
            p = strchr(p, ',')+1;
            steps[i] = step;
            scales[i] = scale;
        }
        net->scales = scales;
        net->steps = steps;
        net->num_steps = n;
    } else if (net->policy == EXP){
        net->gamma = option_find_float(options, "gamma", 1);
    } else if (net->policy == SIG){
        net->gamma = option_find_float(options, "gamma", 1);
        net->step = option_find_int(options, "step", 1);
    } else if (net->policy == POLY || net->policy == RANDOM){
    }
    net->max_batches = option_find_int(options, "max_batches", 0);
}

int is_network(section *s)
{
    return (strcmp(s->type, "[net]")==0
            || strcmp(s->type, "[network]")==0);
}

network *parse_network_cfg(char *filename)
{
    list *sections = read_cfg(filename);
    node *n = sections->front;
    if(!n) error("Config file has no sections");
    network *net = make_network(sections->size - 1);
    net->gpu_index = -1;
    size_params params;

    section *s = (section *)n->val;
    list *options = s->options;
    if(!is_network(s)) error("First section must be [net] or [network]");
    parse_net_options(options, net);

    params.h = net->h;
    params.w = net->w;
    params.c = net->c;
    params.inputs = net->inputs;
    params.batch = net->batch;
    params.time_steps = net->time_steps;
    params.net = net;

    size_t workspace_size = 0;
    n = n->next;
    int count = 0;
    free_section(s);
    fprintf(stderr, "layer     filters    size              input                output\n");
    while(n){
        params.index = count;
        fprintf(stderr, "%5d ", count);
        s = (section *)n->val;
        options = s->options;
        //layer l = {0};
		layer l;
		memset(&l,0,sizeof(layer));
        LAYER_TYPE lt = string_to_layer_type(s->type);
        if(lt == CONVOLUTIONAL){
            l = parse_convolutional(options, params);
        }else if(lt == YOLO){
            l = parse_yolo(options, params);
        }else if(lt == ROUTE){
            l = parse_route(options, params, net);
        }else if(lt == UPSAMPLE){
            l = parse_upsample(options, params, net);
        }else if(lt == SHORTCUT){
            l = parse_shortcut(options, params, net);
        }else if(lt == REGION){
            l = parse_region(options, params);
        }else if(lt == YOLO){
            l = parse_yolo(options, params);
        }else if(lt == MAXPOOL){
            l = parse_maxpool(options, params);
        }else if(lt == REORG){
            l = parse_reorg(options, params);        
		
		}else{
            fprintf(stderr, "Type not recognized: %s\n", s->type);
        }
        l.clip = net->clip;
        l.truth = option_find_int_quiet(options, "truth", 0);
        l.onlyforward = option_find_int_quiet(options, "onlyforward", 0);
        l.stopbackward = option_find_int_quiet(options, "stopbackward", 0);
        l.dontsave = option_find_int_quiet(options, "dontsave", 0);
//        l.dontload = option_find_int_quiet(options, "dontload", 0);
      //  l.dontloadscales = option_find_int_quiet(options, "dontloadscales", 0);
        //l.learning_rate_scale = option_find_float_quiet(options, "learning_rate", 1);
        l.smooth = option_find_float_quiet(options, "smooth", 0);
        option_unused(options);
        net->layers[count] = l;
        if (l.workspace_size > workspace_size) workspace_size = l.workspace_size;
        free_section(s);
        n = n->next;
        ++count;
        if(n){
            params.h = l.out_h;
            params.w = l.out_w;
            params.c = l.out_c;
            params.inputs = l.outputs;
        }
    }
    free_list(sections);
    layer out = get_network_output_layer(net);
    net->outputs = out.outputs;
    net->output = out.output;
    //net->input = (float *)calloc(net->inputs*net->batch, sizeof(float));

	workspace_size = 0;//donot calloc workspace
    //if(workspace_size){
    //    //printf("%ld\n", workspace_size);
    //    net->workspace = (float *)calloc(1, workspace_size);

    //}
    return net;
}

list *read_cfg(char *filename)
{
    FILE *file = fopen(filename, "r");
    if(file == 0) file_error(filename);
    char *line;
    int nu = 0;
    list *options = make_list();
    section *current = 0;
    while((line=fgetl(file)) != 0){
        ++ nu;
        strip(line);
        switch(line[0]){
            case '[':
                current = (section *)malloc(sizeof(section));
                list_insert(options, current);
                current->options = make_list();
                current->type = line;
                break;
            case '\0':
            case '#':
            case ';':
                free(line);
                break;
            default:
                if(!read_option(line, current->options)){
                    fprintf(stderr, "Config file error line %d, could parse: %s\n", nu, line);
                    free(line);
                }
                break;
        }
    }
    fclose(file);
    return options;
}

void load_convolutional_weights(layer l, FILE *fp)
{
    int num = l.nweights;
    fread(l.biases, sizeof(float), l.n, fp);
    if (l.batch_normalize){
        fread(l.scales, sizeof(float), l.n, fp);
        fread(l.rolling_mean, sizeof(float), l.n, fp);
        fread(l.rolling_variance, sizeof(float), l.n, fp);
    }
    fread(l.weights, sizeof(float), num, fp);

}


void load_weights_upto(network *net, char *filename, int start, int cutoff)
{
    fprintf(stderr, "Loading weights from %s...", filename);
    fflush(stdout);
    FILE *fp = fopen(filename, "rb");
    if(!fp) file_error(filename);

    int major;
    int minor;
    int revision;
    fread(&major, sizeof(int), 1, fp);
    fread(&minor, sizeof(int), 1, fp);
    fread(&revision, sizeof(int), 1, fp);
	printf("major=%d;minor=%d;revision=%d\n",major,minor,revision);// 0 2 0
	printf("if true ro false:%d\n",(major*10 + minor) >= 2 && major < 1000 && minor < 1000);
    if ((major*10 + minor) >= 2 && major < 1000 && minor < 1000){
        //fread(net->seen, sizeof(size_t), 1, fp);
		fread(net->seen, sizeof(size_t), 1, fp);
		fread(net->seen, sizeof(size_t), 1, fp);
	}else {
        int iseen = 0;
        fread(&iseen, sizeof(int), 1, fp);
        *net->seen = iseen;
    }

	//printf("sizeof(size_t)=%u\n",sizeof(size_t));// in my PC is 4

    int i;
    for(i = start; i < net->n && i < cutoff; ++i){
        layer l = net->layers[i];
        if(l.type == CONVOLUTIONAL){
            load_convolutional_weights(l, fp);
        }
    }
    fprintf(stderr, "Done!\n");
    fclose(fp);
}

void load_weights(network *net, char *filename)
{
    load_weights_upto(net, filename, 0, net->n);
}
/////////////////praser end

/////////////////network begin
load_args get_base_args(network *net)
{
    load_args args = {0};
    args.w = net->w;
    args.h = net->h;
    args.size = net->w;

    args.min = net->min_crop;
    args.max = net->max_crop;
    args.angle = net->angle;
    args.aspect = net->aspect;
    args.exposure = net->exposure;
    args.center = net->center;
    args.saturation = net->saturation;
    args.hue = net->hue;
    return args;
}

network *load_network(char *cfg, char *weights, int clear)
{
    network *net = parse_network_cfg(cfg);
    //if(weights && weights[0] != 0){
    //    load_weights(net, weights);
    //}
    if(clear) (*net->seen) = 0;
    return net;
}

char *get_layer_string(LAYER_TYPE a)
{
    switch(a){
        case CONVOLUTIONAL:
            return "convolutional";
        case ACTIVE:
            return "activation";
        case LOCAL:
            return "local";
        case DECONVOLUTIONAL:
            return "deconvolutional";
        case CONNECTED:
            return "connected";
        case RNN:
            return "rnn";
        case GRU:
            return "gru";
        case LSTM:
	    return "lstm";
        case CRNN:
            return "crnn";
        case MAXPOOL:
            return "maxpool";
        case REORG:
            return "reorg";
        case AVGPOOL:
            return "avgpool";
        case SOFTMAX:
            return "softmax";
        case DETECTION:
            return "detection";
        case REGION:
            return "region";
        case YOLO:
            return "yolo";
        case DROPOUT:
            return "dropout";
        case CROP:
            return "crop";
        case COST:
            return "cost";
        case ROUTE:
            return "route";
        case SHORTCUT:
            return "shortcut";
        case NORMALIZATION:
            return "normalization";
        case BATCHNORM:
            return "batchnorm";
        default:
            break;
    }
    return "none";
}

network *make_network(int n)
{
    network *net = (network *)calloc(1, sizeof(network));
    net->n = n;
    net->layers = (layer *)calloc(net->n, sizeof(layer));
    net->seen = (size_t *)calloc(1, sizeof(size_t));
    net->t    = (int *)calloc(1, sizeof(int));
    net->cost = (float *)calloc(1, sizeof(float));
    return net;
}

void forward_network(network *netp)
{
    network net = *netp;
    int i;
    for(i = 0; i < net.n; ++i){
        net.index = i;
        layer l = net.layers[i];
        l.forward(l, net);
        net.input = l.output;

	//	printf("layer [%d]\n",i);
    }
 
}


void set_temp_network(network *net, float t)
{
    int i;
    for(i = 0; i < net->n; ++i){
        net->layers[i].temperature = t;
    }
}

void set_batch_network(network *net, int b)
{
    net->batch = b;
    int i;
    for(i = 0; i < net->n; ++i){
        net->layers[i].batch = b;
    }
}

float *network_predict(network *net, float *input)
{
    network orig = *net;
    net->input = input;
    net->truth = 0;
    net->train = 0;
    net->delta = 0;
    forward_network(net);
    float *out = net->output;
    *net = orig;
    return out;
}

int yolo_num_detections(layer l, float thresh)
{
    int i, n;
    int count = 0;
    for (i = 0; i < l.w*l.h; ++i){
        for(n = 0; n < l.n; ++n){
            int obj_index  = entry_index(l, 0, n*l.w*l.h + i, 4);
            if(l.output[obj_index] > thresh){
                ++count;
            }
        }
    }
    return count;
}

int num_detections(network *net, float thresh)
{
    int i;
    int s = 0;
    for(i = 0; i < net->n; ++i){
        layer l = net->layers[i];
        if(l.type == YOLO){
            s += yolo_num_detections(l, thresh);
        }
        if(l.type == DETECTION || l.type == REGION){
            s += l.w*l.h*l.n;
        }
    }
    return s;
}

detection *make_network_boxes(network *net, float thresh, int *num)
{
    layer l = net->layers[net->n - 1];
    int i;
    int nboxes = num_detections(net, thresh);
	//printf("num_detections nboxes = %d\n",nboxes);
    if(num) *num = nboxes;
    detection *dets = (detection *)calloc(nboxes, sizeof(detection));
    for(i = 0; i < nboxes; ++i){
        dets[i].prob = (float *)calloc(l.classes, sizeof(float));
    }
    return dets;
}

box get_yolo_box(float *x, float *biases, int n, int index, int i, int j, int lw, int lh, int w, int h, int stride)
{
    box b;
    b.x = (i + x[index + 0*stride]) / lw;
    b.y = (j + x[index + 1*stride]) / lh;
    b.w = exp(x[index + 2*stride]) * biases[2*n]   / w;
    b.h = exp(x[index + 3*stride]) * biases[2*n+1] / h;
    return b;
}

void correct_yolo_boxes(detection *dets, int n, int w, int h, int netw, int neth, int relative)
{
    int i;
    int new_w=0;
    int new_h=0;
    if (((float)netw/w) < ((float)neth/h)) {
        new_w = netw;
        new_h = (h * netw)/w;
    } else {
        new_h = neth;
        new_w = (w * neth)/h;
    }
    for (i = 0; i < n; ++i){
        box b = dets[i].bbox;
        b.x =  (b.x - (netw - new_w)/2./netw) / ((float)new_w/netw); 
        b.y =  (b.y - (neth - new_h)/2./neth) / ((float)new_h/neth); 
        b.w *= (float)netw/new_w;
        b.h *= (float)neth/new_h;
        if(!relative){
            b.x *= w;
            b.w *= w;
            b.y *= h;
            b.h *= h;
        }
        dets[i].bbox = b;
    }
}


int get_yolo_detections(layer l, int w, int h, int netw, int neth, float thresh, int *map, int relative, detection *dets)
{
    int i,j,n;
    float *predictions = l.output;
   // if (l.batch == 2) avg_flipped_yolo(l);
    int count = 0;
    for (i = 0; i < l.w*l.h; ++i){
        int row = i / l.w;
        int col = i % l.w;
        for(n = 0; n < l.n; ++n){
            int obj_index  = entry_index(l, 0, n*l.w*l.h + i, 4);
            float objectness = predictions[obj_index];
            if(objectness <= thresh) continue;
            int box_index  = entry_index(l, 0, n*l.w*l.h + i, 0);
            dets[count].bbox = get_yolo_box(predictions, l.biases, l.mask[n], box_index, col, row, l.w, l.h, netw, neth, l.w*l.h);
            dets[count].objectness = objectness;
            dets[count].classes = l.classes;
            for(j = 0; j < l.classes; ++j){
                int class_index = entry_index(l, 0, n*l.w*l.h + i, 4 + 1 + j);
                float prob = objectness*predictions[class_index];
                dets[count].prob[j] = (prob > thresh) ? prob : 0;
            }
            ++count;
        }
    }
    correct_yolo_boxes(dets, count, w, h, netw, neth, relative);
    return count;
}

box get_region_box(float *x, float *biases, int n, int index, int i, int j, int w, int h, int stride)
{
    box b;
    b.x = (i + x[index + 0*stride]) / w;
    b.y = (j + x[index + 1*stride]) / h;
    b.w = exp(x[index + 2*stride]) * biases[2*n]   / w;
    b.h = exp(x[index + 3*stride]) * biases[2*n+1] / h;
    return b;
}

void correct_region_boxes(detection *dets, int n, int w, int h, int netw, int neth, int relative)
{
    int i;
    int new_w=0;
    int new_h=0;
    if (((float)netw/w) < ((float)neth/h)) {
        new_w = netw;
        new_h = (h * netw)/w;
    } else {
        new_h = neth;
        new_w = (w * neth)/h;
    }
    for (i = 0; i < n; ++i){
        box b = dets[i].bbox;
        b.x =  (b.x - (netw - new_w)/2./netw) / ((float)new_w/netw); 
        b.y =  (b.y - (neth - new_h)/2./neth) / ((float)new_h/neth); 
        b.w *= (float)netw/new_w;
        b.h *= (float)neth/new_h;
        if(!relative){
            b.x *= w;
            b.w *= w;
            b.y *= h;
            b.h *= h;
        }
        dets[i].bbox = b;
    }
}

void get_region_detections(layer l, int w, int h, int netw, int neth, float thresh, int *map, float tree_thresh, int relative, detection *dets)
{
    int i,j,n,z;
    float *predictions = l.output;
    if (l.batch == 2) {
        float *flip = l.output + l.outputs;
        for (j = 0; j < l.h; ++j) {
            for (i = 0; i < l.w/2; ++i) {
                for (n = 0; n < l.n; ++n) {
                    for(z = 0; z < l.classes + l.coords + 1; ++z){
                        int i1 = z*l.w*l.h*l.n + n*l.w*l.h + j*l.w + i;
                        int i2 = z*l.w*l.h*l.n + n*l.w*l.h + j*l.w + (l.w - i - 1);
                        float swap = flip[i1];
                        flip[i1] = flip[i2];
                        flip[i2] = swap;
                        if(z == 0){
                            flip[i1] = -flip[i1];
                            flip[i2] = -flip[i2];
                        }
                    }
                }
            }
        }
        for(i = 0; i < l.outputs; ++i){
            l.output[i] = (l.output[i] + flip[i])/2.;
        }
    }
    for (i = 0; i < l.w*l.h; ++i){
        int row = i / l.w;
        int col = i % l.w;
        for(n = 0; n < l.n; ++n){
            int index = n*l.w*l.h + i;
            for(j = 0; j < l.classes; ++j){
                dets[index].prob[j] = 0;
            }
            int obj_index  = entry_index(l, 0, n*l.w*l.h + i, l.coords);
            int box_index  = entry_index(l, 0, n*l.w*l.h + i, 0);
            int mask_index = entry_index(l, 0, n*l.w*l.h + i, 4);
            float scale = l.background ? 1 : predictions[obj_index];
            dets[index].bbox = get_region_box(predictions, l.biases, n, box_index, col, row, l.w, l.h, l.w*l.h);
            dets[index].objectness = scale > thresh ? scale : 0;
            if(dets[index].mask){
                for(j = 0; j < l.coords - 4; ++j){
                    dets[index].mask[j] = l.output[mask_index + j*l.w*l.h];
                }
            }

            int class_index = entry_index(l, 0, n*l.w*l.h + i, l.coords + !l.background);

            if(dets[index].objectness){
                for(j = 0; j < l.classes; ++j){
                    int class_index = entry_index(l, 0, n*l.w*l.h + i, l.coords + 1 + j);
                    float prob = scale*predictions[class_index];
                    dets[index].prob[j] = (prob > thresh) ? prob : 0;
                }
            }

        }
    }
    correct_region_boxes(dets, l.w*l.h*l.n, w, h, netw, neth, relative);
}

void fill_network_boxes(network *net, int w, int h, float thresh, float hier, int *map, int relative, detection *dets)
{
    int j;
    for(j = 0; j < net->n; ++j){
        layer l = net->layers[j];
        if(l.type == YOLO){
            int count = get_yolo_detections(l, w, h, net->w, net->h, thresh, map, relative, dets);
            dets += count;
        }
        if(l.type == REGION){
            get_region_detections(l, w, h, net->w, net->h, thresh, map, hier, relative, dets);
            dets += l.w*l.h*l.n;
        }
    }
}

detection *get_network_boxes(network *net, int w, int h, float thresh, float hier, int *map, int relative, int *num)
{
    detection *dets = make_network_boxes(net, thresh, num);
    fill_network_boxes(net, w, h, thresh, hier, map, relative, dets);
    return dets;
}

void free_detections(detection *dets, int n)
{
    int i;
    for(i = 0; i < n; ++i){
        free(dets[i].prob);
        if(dets[i].mask) free(dets[i].mask);
    }
    free(dets);
}

int network_width(network *net){return net->w;}
int network_height(network *net){return net->h;}

layer get_network_output_layer(network *net)
{
    int i;
    for(i = net->n - 1; i >= 0; --i){
        if(net->layers[i].type != COST) break;
    }
    return net->layers[i];
}

void free_network(network *net)
{
    int i;
    for(i = 0; i < net->n; ++i){
        free_layer(net->layers[i]);
    }
    free(net->layers);
    if(net->input) free(net->input);
    if(net->truth) free(net->truth);

    free(net);
}

layer network_output_layer(network *net)
{
    int i;
    for(i = net->n - 1; i >= 0; --i){
        if(net->layers[i].type != COST) break;
    }
    return net->layers[i];
}

int network_inputs(network *net)
{
    return net->layers[0].inputs;
}

int network_outputs(network *net)
{
    return network_output_layer(net).outputs;
}

float *network_output(network *net)
{
    return network_output_layer(net).output;
}

//////////////////network end

//////////////////////box begin

int nms_comparator(const void *pa, const void *pb)
{
    detection a = *(detection *)pa;
    detection b = *(detection *)pb;
    float diff = 0;
    if(b.sort_class >= 0){
        diff = a.prob[b.sort_class] - b.prob[b.sort_class];
    } else {
        diff = a.objectness - b.objectness;
    }
    if(diff < 0) return 1;
    else if(diff > 0) return -1;
    return 0;
}

float overlap(float x1, float w1, float x2, float w2)
{
    float l1 = x1 - w1/2;
    float l2 = x2 - w2/2;
    float left = l1 > l2 ? l1 : l2;
    float r1 = x1 + w1/2;
    float r2 = x2 + w2/2;
    float right = r1 < r2 ? r1 : r2;
    return right - left;
}

float box_intersection(box a, box b)
{
    float w = overlap(a.x, a.w, b.x, b.w);
    float h = overlap(a.y, a.h, b.y, b.h);
    if(w < 0 || h < 0) return 0;
    float area = w*h;
    return area;
}

float box_union(box a, box b)
{
    float i = box_intersection(a, b);
    float u = a.w*a.h + b.w*b.h - i;
    return u;
}

float box_iou(box a, box b)
{
    return box_intersection(a, b)/box_union(a, b);
}

void do_nms_sort(detection *dets, int total, int classes, float thresh)
{
    int i, j, k;
    k = total-1;
    for(i = 0; i <= k; ++i){
        if(dets[i].objectness == 0){
            detection swap = dets[i];
            dets[i] = dets[k];
            dets[k] = swap;
            --k;
            --i;
        }
    }
    total = k+1;

    for(k = 0; k < classes; ++k){
        for(i = 0; i < total; ++i){
            dets[i].sort_class = k;
        }
        qsort(dets, total, sizeof(detection), nms_comparator);
        for(i = 0; i < total; ++i){
            if(dets[i].prob[k] == 0) continue;
            box a = dets[i].bbox;
            for(j = i+1; j < total; ++j){
                box b = dets[j].bbox;
                if (box_iou(a, b) > thresh){
                    dets[j].prob[k] = 0;
                }
            }
        }
    }
}
//////////////////////box end

//////////////////////image begin

float colors[6][3] = { {1,0,1}, {0,0,1},{0,1,1},{0,1,0},{1,1,0},{1,0,0} };

float get_color(int c, int x, int max)
{
    float ratio = ((float)x/max)*5;
    int i = floor(ratio);
    int j = ceil(ratio);
    ratio -= i;
    float r = (1-ratio) * colors[i][c] + ratio*colors[j][c];
    //printf("%f\n", r);
    return r;
}

static float get_pixel_extend(image m, int x, int y, int c)
{
    if(x < 0 || x >= m.w || y < 0 || y >= m.h) return 0;
    /*
    if(x < 0) x = 0;
    if(x >= m.w) x = m.w-1;
    if(y < 0) y = 0;
    if(y >= m.h) y = m.h-1;
    */
    if(c < 0 || c >= m.c) return 0;
    return get_pixel(m, x, y, c);
}

void composite_image(image source, image dest, int dx, int dy)
{
    int x,y,k;
    for(k = 0; k < source.c; ++k){
        for(y = 0; y < source.h; ++y){
            for(x = 0; x < source.w; ++x){
                float val = get_pixel(source, x, y, k);
                float val2 = get_pixel_extend(dest, dx+x, dy+y, k);
                set_pixel(dest, dx+x, dy+y, k, val * val2);
            }
        }
    }
}

image border_image(image a, int border)
{
    image b = make_image(a.w + 2*border, a.h + 2*border, a.c);
    int x,y,k;
    for(k = 0; k < b.c; ++k){
        for(y = 0; y < b.h; ++y){
            for(x = 0; x < b.w; ++x){
                float val = get_pixel_extend(a, x - border, y - border, k);
                if(x - border < 0 || x - border >= a.w || y - border < 0 || y - border >= a.h) val = 1;
                set_pixel(b, x, y, k, val);
            }
        }
    }
    return b;
}

image copy_image(image p)
{
    image copy = p;
    copy.data = (float *)calloc(p.h*p.w*p.c, sizeof(float));
    memcpy(copy.data, p.data, p.h*p.w*p.c*sizeof(float));
    return copy;
}

image tile_images(image a, image b, int dx)
{
    if(a.w == 0) return copy_image(b);
    image c = make_image(a.w + b.w + dx, (a.h > b.h) ? a.h : b.h, (a.c > b.c) ? a.c : b.c);
    fill_cpu(c.w*c.h*c.c, 1, c.data, 1);
    embed_image(a, c, 0, 0); 
    composite_image(b, c, a.w + dx, 0);
    return c;
}

image get_label(image **characters, char *string, int size)
{
    size = size/10;
    if(size > 7) size = 7;
    image label = make_empty_image(0,0,0);
    while(*string){
        image l = characters[size][(int)*string];
        image n = tile_images(label, l, -size - 1 + (size+1)/2);
        free_image(label);
        label = n;
        ++string;
    }
    image b = border_image(label, label.h*.25);
    free_image(label);
    return b;
}

void draw_label(image a, int r, int c, image label, const float *rgb)
{
    int w = label.w;
    int h = label.h;
    if (r - h >= 0) r = r - h;

    int i, j, k;
    for(j = 0; j < h && j + r < a.h; ++j){
        for(i = 0; i < w && i + c < a.w; ++i){
            for(k = 0; k < label.c; ++k){
                float val = get_pixel(label, i, j, k);
                set_pixel(a, i+c, j+r, k, rgb[k] * val);
            }
        }
    }
}

void draw_box(image a, int x1, int y1, int x2, int y2, float r, float g, float b)
{
    //normalize_image(a);
    int i;
    if(x1 < 0) x1 = 0;
    if(x1 >= a.w) x1 = a.w-1;
    if(x2 < 0) x2 = 0;
    if(x2 >= a.w) x2 = a.w-1;

    if(y1 < 0) y1 = 0;
    if(y1 >= a.h) y1 = a.h-1;
    if(y2 < 0) y2 = 0;
    if(y2 >= a.h) y2 = a.h-1;

    for(i = x1; i <= x2; ++i){
        a.data[i + y1*a.w + 0*a.w*a.h] = r;
        a.data[i + y2*a.w + 0*a.w*a.h] = r;

        a.data[i + y1*a.w + 1*a.w*a.h] = g;
        a.data[i + y2*a.w + 1*a.w*a.h] = g;

        a.data[i + y1*a.w + 2*a.w*a.h] = b;
        a.data[i + y2*a.w + 2*a.w*a.h] = b;
    }
    for(i = y1; i <= y2; ++i){
        a.data[x1 + i*a.w + 0*a.w*a.h] = r;
        a.data[x2 + i*a.w + 0*a.w*a.h] = r;

        a.data[x1 + i*a.w + 1*a.w*a.h] = g;
        a.data[x2 + i*a.w + 1*a.w*a.h] = g;

        a.data[x1 + i*a.w + 2*a.w*a.h] = b;
        a.data[x2 + i*a.w + 2*a.w*a.h] = b;
    }
}

void draw_box_width(image a, int x1, int y1, int x2, int y2, int w, float r, float g, float b)
{
    int i;
    for(i = 0; i < w; ++i){
        draw_box(a, x1+i, y1+i, x2-i, y2-i, r, g, b);
    }
}

image float_to_image(int w, int h, int c, float *data)
{
    image out = make_empty_image(w,h,c);
    out.data = data;
    return out;
}

image threshold_image(image im, float thresh)
{
    int i;
    image t = make_image(im.w, im.h, im.c);
    for(i = 0; i < im.w*im.h*im.c; ++i){
        t.data[i] = im.data[i]>thresh ? 1 : 0;
    }
    return t;
}

void draw_detections(image im, detection *dets, int num, float thresh, char **names, image **alphabet, int classes)
{
    int i,j;

    for(i = 0; i < num; ++i){
        char labelstr[4096] = {0};
        int class_t = -1;
        for(j = 0; j < classes; ++j){
            if (dets[i].prob[j] > thresh){
                if (class_t < 0) {
                    strcat(labelstr, names[j]);
                    class_t = j;
                } else {
                    strcat(labelstr, ", ");
                    strcat(labelstr, names[j]);
                }
                printf("%s: %.0f%%\n", names[j], dets[i].prob[j]*100);
            }
        }
        if(class_t >= 0){
            int width = im.h * .006;
            //printf("%d %s: %.0f%%\n", i, names[class], prob*100);
            int offset = class_t*123457 % classes;
            float red = get_color(2,offset,classes);
            float green = get_color(1,offset,classes);
            float blue = get_color(0,offset,classes);
            float rgb[3];

            //width = prob*20+2;

            rgb[0] = red;
            rgb[1] = green;
            rgb[2] = blue;
            box b = dets[i].bbox;
            //printf("%f %f %f %f\n", b.x, b.y, b.w, b.h);

            int left  = (b.x-b.w/2.)*im.w;
            int right = (b.x+b.w/2.)*im.w;
            int top   = (b.y-b.h/2.)*im.h;
            int bot   = (b.y+b.h/2.)*im.h;

            if(left < 0) left = 0;
            if(right > im.w-1) right = im.w-1;
            if(top < 0) top = 0;
            if(bot > im.h-1) bot = im.h-1;

            draw_box_width(im, left, top, right, bot, width, red, green, blue);
            if (alphabet) {
                image label = get_label(alphabet, labelstr, (im.h*.03));
                draw_label(im, top + width, left, label, rgb);
                free_image(label);
            }
            if (dets[i].mask){
                image mask = float_to_image(14, 14, 1, dets[i].mask);
                image resized_mask = resize_image(mask, b.w*im.w, b.h*im.h);
                image tmask = threshold_image(resized_mask, .5);
                embed_image(tmask, im, left, top);
                free_image(mask);
                free_image(resized_mask);
                free_image(tmask);
            }
        }
    }
}

//////////////////////image end



///////////////////////////////////////////////////////////////////////20181229 reorg WeightQ BetaQ ok  InputQ ok start input opt ok input_g eval op1 wuxiaoguo layer1 still 0.14s relu opt // input opt ok //output opt ok// wieght opt ok //out4 gg (5)n4m32i4o2 ok //20190319 modify some bugs in output TR_MIN
//#define MAX(x,y) ((x)>(y)?(x):(y))
//#define MIN(x,y) ((x)<(y)?(x):(y))
//
//float mm(int Length,int MAX_BurstLenth)//100MHz MAX_burstlength 1-256;Length 32bit
//{
//	static float burst_speed[256] = {
//	15.05800533,29.34379959,42.38548279,55.42713928,66.22721863,77.78242493,87.62513733,98.15619659,107.29577637,116.79578400,125.73155212,134.63140869,
//	141.88391113,148.38928223,156.07928467,163.48634338,170.14941406,177.13075256,181.25485229,187.66236877,193.85479736,199.86259460,203.14558411,209.22280884,
//	213.59533691,218.88497925,221.76406860,228.32760620,230.62730408,235.31747437,239.19511414,243.42375183,248.04182434,252.41569519,256.00204468,260.51312256,
//	262.14251709,268.57128906,271.75299072,275.59240723,278.83673096,282.65679932,285.17068481,288.78131104,291.79641724,295.63247681,298.81549072,301.10278320,
//	304.47772217,307.27130127,309.20263672,312.71987915,314.80880737,318.11676025,320.49996948,323.66714478,326.11132812,328.03018188,330.33621216,332.81158447,
//	335.37176514,337.15087891,339.76406860,339.08181763,344.37857056,346.02075195,348.17236328,350.02899170,352.33752441,353.58529663,355.75714111,357.36819458,
//	359.96310425,361.75564575,363.07525635,365.12591553,366.73275757,367.72943115,369.98068237,371.05322266,373.37594604,374.69409180,376.81637573,378.29977417,
//	379.45263672,380.83676147,382.36120605,384.13751221,385.14309692,386.82614136,386.37542725,389.87066650,390.82537842,392.14004517,393.50469971,394.79852295,
//	395.65277100,397.14306641,398.12384033,400.01998901,401.01757812,401.88888550,403.36050415,404.34927368,404.94284058,406.53247070,407.24127197,408.88299561,
//	409.66293335,411.19213867,412.14807129,412.79403687,413.89123535,414.95388794,416.26556396,416.86749268,417.96737671,417.39764404,420.16253662,420.72879028,
//	421.67681885,422.52032471,423.63345337,424.11349487,425.22940063,425.69323730,427.26483154,428.31137085,428.70156860,429.70611572,430.31573486,430.62844849,
//	431.84301758,432.36230469,433.64840698,434.03955078,435.16101074,435.91384888,436.47274780,437.22418213,437.87030029,439.00265503,439.38238525,440.08636475,
//	439.53326416,441.79367065,442.21493530,442.83609009,443.55117798,444.35803223,444.68222046,445.45291138,445.71969604,447.06472778,447.58062744,447.90951538,
//	448.83303833,449.37823486,449.52343750,450.28564453,450.82168579,451.87210083,452.07318115,452.95303345,453.47616577,453.97476196,454.44863892,454.81356812,
//	455.87615967,456.19461060,456.67639160,456.08407593,458.02291870,458.26889038,458.78137207,459.50274658,459.96176147,460.23300171,460.84609985,460.99877930,
//	462.05383301,462.45446777,462.68850708,463.36853027,463.81854248,463.96310425,464.64352417,464.98785400,465.86788940,465.97305298,466.61175537,467.02032471,
//	467.45355225,467.70974731,468.26071167,468.94006348,469.22540283,469.52145386,469.04315186,470.62976074,470.83404541,471.17373657,471.84417725,472.15051270,
//	472.36654663,472.87960815,472.98446655,473.80032349,474.16189575,474.35165405,474.84439087,475.15460205,475.35223389,475.91427612,476.19403076,476.90371704,
//	476.92501831,477.48367310,477.90081787,478.21862793,478.43313599,478.92361450,479.32894897,479.50131226,479.71697998,479.32174683,480.73312378,480.87759399,
//	481.11618042,481.64843750,481.96038818,482.14916992,482.54544067,482.58181763,483.29241943,483.58822632,483.76000977,484.05273438,484.33847046,484.51446533,
//	485.07998657,485.27493286,485.82012939,485.89019775,486.26675415,486.70312500,486.99197388,487.09207153,487.57818604,487.81231689,488.12112427,488.15835571,
//	487.70080566,488.99755859,489.16574097,489.77218628
//	};
//
//	float latency = 0.0;
//	int Loops = Length/MAX_BurstLenth;
//	latency = Loops*MAX_BurstLenth*4.0/1024/1024/burst_speed[MAX_BurstLenth-1];
//	int others = Length%MAX_BurstLenth;
//	if(others!=0)
//		latency += others*4.0/1024/1024/burst_speed[others-1];
//	return latency;
//}
//
////#define S 2
////#define K 3
////
////#define Tn 4
////#define Tm 32
////#define Tr 26
////#define Tc 26
//
////#define OnChipIB_Width  ((Tc-1)*S+K)
////#define OnChipIB_Height ((Tr-1)*S+K)
//
//double design_space_explore(network *net,int S,int K,int Tn,int Tm,int Tr,int Tc,int *Nma_total)
//{
//	int Nma_in,Nma_out,Nma_w;
//	int x;
//
//	int OnChipIB_Width  = ((Tc-1)*S+K);
//	int OnChipIB_Height = ((Tr-1)*S+K);
//
//	network orig = *net;
//
//	float *region_buf = (float *)calloc(sizeof(float),13*13*425); 
//    network netp = *net;
//    int i;
//	int TR,TC,TM,TN;
//	int output_w,output_h;
//	int rLoops,cLoops,mLoops,nLoops;
//	double sum_gop = 0.0;
//
////////////////eval start
//	int T2Rate,ColIncreaseLength;
//	int trow_loops;
//	int omLoops,orLoops;
//	const int Cin = 4;
//	const int Cout = 2;
//	const float freq = 150000000;
//	const int rw_fm_max_burstlength = 64;
//	const int r_wb_max_burstlength = 128;
//	float load_ifm,load_w,compute,store_ofm;
//	float load_w1,load_w2;
//	float store_o1,store_o2;
//	float load_ifm1,load_ifm2;
//	float layper_latency;
//	float inner_loop_latency;
//	float load_ifm_latency,load_w_latency,compute_latency,store_ofm_latency;
//	float load_ifm_latency_array[32];
//	float load_w_latency_array[32];
//	float compute_latency_array[32];
//	float store_ofm_latency_array[32];
//	float layper_latency_array[32];
//	double sum_latency;
//	int latency_cnt = 0;
//	int TRow;
//	int TCol;
////////////////eval end
//
//	*Nma_total = 0.0;
//    for(i = 0; i < netp.n; ++i)
//	{
//        netp.index = i;
//        layer l = netp.layers[i];
//		//printf("Layer[%2d]: ",i);
//		switch(l.type)
//		{
//			case CONVOLUTIONAL:
//				//printf("outputMemory:%8d;BN=%d;Activation=%d;conv  %5d %2d x%2d /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d  %5.3f BFLOPs\n",l.outputs,l.batch_normalize,l.activation, l.n, l.size, l.size, l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c, (2.0 * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w)/1000000000.);
//				sum_gop += (2.0 * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w)/1000000000.;
//				output_w = (l.w - l.size + 2*l.pad)/l.stride + 1 ;
//				output_h = (l.h - l.size + 2*l.pad)/l.stride + 1 ;
//
//				TR = MIN(((OnChipIB_Height-l.size)/l.stride+1),Tr);//keep Kernel_stride>=1
//				TR = MIN(output_h,TR);
//				TC = MIN(((OnChipIB_Width-l.size)/l.stride+1),Tc);
//				TC = MIN(output_w,TC);
//				TM = MIN(l.n,Tm);
//				TN = MIN(l.c,Tn);
//
//				rLoops = (int)ceil(((float)output_h)/TR);
//				cLoops = (int)ceil(((float)output_w)/TC);
//				mLoops = (int)ceil(((float)l.n)/TM);
//			    nLoops = (int)ceil(((float)l.c)/TN);
//			
//				TRow = (TR-1)*l.stride+l.size;
//				TCol = (TC-1)*l.stride+l.size;
//				switch(l.w)
//				{
//					case 26:
//						T2Rate = 2;
//						break;
//					case 13:
//						T2Rate = 4;
//						break;
//					default:
//						T2Rate = 1;
//						break;
//				}
//
//				//load_ifm1 = 5/freq + mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
//				//load_ifm2 = 5/freq + T2Rate*TCol/freq;
//				load_ifm1 = 5/freq + TN*mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
//				load_ifm2 = 5/freq + TN*T2Rate*TCol/freq;
//				trow_loops = (int)ceil(((float)TRow/T2Rate));
//				load_ifm = 15/freq + load_ifm1 + load_ifm2 + (trow_loops-1)*MAX(load_ifm1,load_ifm2);
//
//				load_w1 = (Tm*Tn+10)/freq;
//				load_w2 = 5/freq + mm(TM*TN/2,r_wb_max_burstlength);
//				load_w = l.size*(load_w1 + load_w2 + (l.size-1)*MAX(load_w1,load_w2));
//
//				compute = (10 + l.size*l.size*TR*TC)/freq;
//
//				store_o1 = mm((TC == 26)?13:169,rw_fm_max_burstlength);
//				store_o2 = (5 + ((TC == 26)?26:2*13*13))/freq;
//
//				//if(TM > Tm/2)
//				//{
//				//	omLoops = Tm/2;
//				//}else
//				//{
//				//	omLoops = TM;
//				//}
//
//				omLoops = TM;
//				if(TC == 26)
//				{
//					orLoops = 26;
//				}else//TMxTRxTC TMx13x13 continues
//				{
//					orLoops = 1;
//					omLoops = omLoops/2;
//				}
//
//				store_ofm = (30)/freq + omLoops*(store_o1 + store_o2 + (orLoops-1)*MAX(store_o1,store_o2));
//
//				load_ifm_latency = rLoops*cLoops*mLoops*nLoops*load_ifm;
//				load_w_latency = rLoops*cLoops*mLoops*nLoops*load_w;
//				store_ofm_latency = rLoops*cLoops*mLoops*store_ofm;
//				compute_latency = rLoops*cLoops*mLoops*(nLoops*compute+TM/freq);
//				inner_loop_latency = ((nLoops-1)*MAX(MAX(load_ifm,load_w),compute)+MAX(load_ifm,load_w)+compute);
//				layper_latency = rLoops*cLoops*((mLoops-1)*MAX(inner_loop_latency,store_ofm)+inner_loop_latency+store_ofm);
//
//				load_ifm_latency_array[latency_cnt] = load_ifm_latency;
//				load_w_latency_array[latency_cnt] = load_w_latency;
//				compute_latency_array[latency_cnt] = compute_latency;
//				store_ofm_latency_array[latency_cnt] = store_ofm_latency;
//				layper_latency_array[latency_cnt] = layper_latency;
//				latency_cnt++;
//				//printf("TR=%d,TC=%d,TM=%d,TN=%d,rLoops=%d,cLoops=%d,mLoops=%d,nLoops=%d\n",TR,TC,TM,TN,rLoops,cLoops,mLoops,nLoops);
//
//				Nma_in = rLoops*cLoops*mLoops*nLoops*TN*TRow*TCol;
//				Nma_out = rLoops*cLoops*mLoops*TM*TR*TC;
//				Nma_w = rLoops*cLoops*mLoops*nLoops*TM*TN*l.size*l.size;
//				*Nma_total += (Nma_in + Nma_out + Nma_w);
//				break;
//			case MAXPOOL:
//				//printf("outputMemory:%8d;max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n",l.outputs, l.size, l.size, l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c);
//				output_w = (l.w - l.size)/l.stride + 1 ;
//				output_h = (l.h - l.size)/l.stride + 1 ;
//
//				TR = MIN(((OnChipIB_Height-l.size)/l.stride+1),Tr);//keep Kernel_stride>=1
//				TC = MIN(((OnChipIB_Width-l.size)/l.stride+1),Tc);
//
//				TR = MIN(output_h,TR);
//				TC = MIN(output_w,TC);
//				TM = MIN(Tm,Tn);
//				TM = MIN(l.c,TM);
//				TN = TM;
//
//				rLoops = (int)ceil(((float)output_h)/TR);
//				cLoops = (int)ceil(((float)output_w)/TC);
//				mLoops = (int)ceil(((float)l.c)/TM);
//
//				TRow = (TR-1)*l.stride+l.size;
//				TCol = (TC-1)*l.stride+l.size;
//				switch(l.w)
//				{
//					case 26:
//						T2Rate = 2;
//						break;
//					case 13:
//						T2Rate = 4;
//						break;
//					default:
//						T2Rate = 1;
//						break;
//				}
//
//				//load_ifm1 = 5/freq + mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
//				//load_ifm2 = 5/freq + T2Rate*TCol/freq;
//				load_ifm1 = 5/freq + TN*mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
//				//printf("mm=%.10lf\n",mm(T2Rate*TCol/2.0,rw_fm_max_burstlength));
//				//printf("load_ifm1=%.10lf\n",load_ifm1);
//				load_ifm2 = 5/freq + TN*T2Rate*TCol/freq;
//				trow_loops = (int)ceil(((float)TRow/T2Rate));
//				load_ifm = 15/freq + load_ifm1 + load_ifm2 + (trow_loops-1)*MAX(load_ifm1,load_ifm2);
//				//printf("load_ifm1=%lf\n",load_ifm1);
//				//printf("load_ifm2=%lf\n",load_ifm2);
//				//printf("trow_loops=%d\n",trow_loops);
//				//printf("load_ifm=%lf\n",load_ifm);
//				compute = (5 + l.size*l.size*TR*TC)/freq;
//
//				store_o1 = mm((TC == 26)?13:169,rw_fm_max_burstlength);
//				store_o2 = (5 + ((TC == 26)?26:2*13*13))/freq;
//
//				//if(TM > Tm/2)
//				//{
//				//	omLoops = Tm/2;
//				//}else
//				//{
//				//	omLoops = TM;
//				//}
//				omLoops = TM;
//				if(TC == 26)
//				{
//					orLoops = 26;
//				}else//TMxTRxTC TMx13x13 continues
//				{
//					orLoops = 1;
//					omLoops = omLoops/2;
//				}
//
//				store_ofm = (30)/freq + omLoops*(store_o1 + store_o2 + (orLoops-1)*MAX(store_o1,store_o2));
//
//				//printf("load_ifm=%lf\n",load_ifm);
//				load_ifm_latency = rLoops*cLoops*mLoops*load_ifm;
//				//printf("load_ifm_latency=%lf\n",load_ifm_latency);
//				store_ofm_latency = rLoops*cLoops*mLoops*store_ofm;
//				//printf("store_ofm_latency=%lf\n",store_ofm_latency);
//				compute_latency = rLoops*cLoops*mLoops*compute;
//				//printf("compute_latency=%lf\n",compute_latency);
//				/*layper_latency = rLoops*cLoops*((mLoops-1)*MAX(load_ifm,store_ofm)+ load_ifm + compute + store_ofm);*/
//				layper_latency = rLoops*cLoops*(mLoops*MAX(load_ifm,MAX(compute,store_ofm))+ load_ifm + store_ofm);
//				//printf("layper_latency=%lf\n",layper_latency);
//				load_ifm_latency_array[latency_cnt] = load_ifm_latency;
//				load_w_latency_array[latency_cnt] = 0;
//				compute_latency_array[latency_cnt] = compute_latency;
//				store_ofm_latency_array[latency_cnt] = store_ofm_latency;
//				layper_latency_array[latency_cnt] = layper_latency;
//				latency_cnt++;
//
//				Nma_in = rLoops*cLoops*mLoops*TN*TRow*TCol;
//				Nma_out = rLoops*cLoops*mLoops*TM*TR*TC;
//				Nma_w = 0;
//				*Nma_total += (Nma_in + Nma_out + Nma_w);
//
//				break;
//			case REORG:
//				//printf("outputMemory:%8d;reorg              /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n",l.outputs,  l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c);			
//				output_w = 26;
//				output_h = 32*13;
//
//				TR = MIN(((OnChipIB_Height-l.stride)/l.stride+1),Tr);//keep Kernel_stride>=1
//				TR = MIN(output_h,TR);
//				TC = MIN(((OnChipIB_Width-l.stride)/l.stride+1),Tc);
//				TC = MIN(output_w,TC);
//				TM = 4;
//				TN = TM;
//
//				rLoops = (int)ceil(((float)output_h)/TR);
//				cLoops = (int)ceil(((float)output_w)/TC);
//				mLoops = 1;
//
//				TRow = (TR-1)*l.stride+l.stride;
//				TCol = (TC-1)*l.stride+l.stride;
//				switch(52)
//				{
//					case 26:
//						T2Rate = 2;
//						break;
//					case 13:
//						T2Rate = 4;
//						break;
//					default:
//						T2Rate = 1;
//						break;
//				}
//
//				load_ifm1 = 5/freq + TN*mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
//				load_ifm2 = 5/freq + TN*T2Rate*TCol/freq;
//				//load_ifm1 = 5/freq + mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
//				//load_ifm2 = 5/freq + T2Rate*TCol/freq;
//				trow_loops = (int)ceil(((float)TRow/T2Rate));
//				load_ifm = 15/freq + load_ifm1 + load_ifm2 + (trow_loops-1)*MAX(load_ifm1,load_ifm2);
//
//				compute = (5 + l.stride*l.stride*TR*TC)/freq;
//
//				store_o1 = mm((TC == 26)?13:169,rw_fm_max_burstlength);
//				store_o2 = (5 + ((TC == 26)?26:2*13*13))/freq;
//
//				//if(TM > Tm/2)
//				//{
//				//	omLoops = Tm/2;
//				//}else
//				//{
//				//	omLoops = TM;
//				//}
//
//				omLoops = TM;
//				if(TC == 26)
//				{
//					orLoops = 26;
//				}else//TMxTRxTC TMx13x13 continues
//				{
//					orLoops = 1;
//					omLoops = omLoops/2;
//				}
//
//				store_ofm = (30)/freq + omLoops*(store_o1 + store_o2 + (orLoops-1)*MAX(store_o1,store_o2));
//
//				load_ifm_latency = rLoops*cLoops*mLoops*load_ifm;
//				store_ofm_latency = rLoops*cLoops*mLoops*store_ofm;
//				compute_latency = rLoops*cLoops*mLoops*compute;
//				//layper_latency = rLoops*cLoops*((mLoops-1)*MAX(load_ifm,store_ofm)+ load_ifm + compute + store_ofm);
//				layper_latency = rLoops*cLoops*(mLoops*MAX(load_ifm,MAX(compute,store_ofm))+ load_ifm + store_ofm);
//
//				load_ifm_latency_array[latency_cnt] = load_ifm_latency;
//				load_w_latency_array[latency_cnt] = 0;
//				compute_latency_array[latency_cnt] = compute_latency;
//				store_ofm_latency_array[latency_cnt] = store_ofm_latency;
//				layper_latency_array[latency_cnt] = layper_latency;
//				latency_cnt++;
//
//				Nma_in = rLoops*cLoops*mLoops*TN*TRow*TCol;
//				Nma_out = rLoops*cLoops*mLoops*TM*TR*TC;
//				Nma_w = 0;
//				*Nma_total += (Nma_in + Nma_out + Nma_w);
//
//				break;
//			case ROUTE:
//				//printf("outputMemory:%8d;route ",l.outputs);
//				//int j;
//				//for(j = 0; j < l.n; ++j){
//				//	printf(" %d", l.input_layers[j]);
//				//}
//				//printf("\n");
//				break;
//			case REGION:
//				//printf("outputMemory:%8d;Detection\n",l.outputs);
//				break;
//		}
//
//		netp.input = l.output;
//    }
//	*net = orig;
//
//	sum_latency = 0.0;
//	for(i=0;i<latency_cnt;i++)
//	{
//		//printf("layper_latency_array[%d]=%lf\n",i,layper_latency_array[i]);
//		sum_latency += layper_latency_array[i];
//	}
//	//printf("sum_latency=%lf\n",sum_latency);
//	//*Nma_total = 1;
//	*Nma_total = *Nma_total;
//	return sum_latency;
//}
//
//void yolov2_hls_ps(network *net, float *input)
//{
//	int x = 0;
//	char line[256];
//	FILE *fp3;
//	char filename[256];
//	sprintf(filename, "explore_%d.txt", 123123);
//    if( (fp3 = fopen(filename, "w")) == NULL)fprintf(stderr,"CANNOT OPEN\n");
//
//	const int S = 2;
//	const int K = 3;
//	const float ModelGOP = 29.4728;
//	int Tn;
//	int Tm;
//	int Tr;
//	int Tc;
//	int Nma_total;
//	int Memory_total;
//	int Mem_in,Mem_out,Mem_inline,Mem_outline,Mem_wline;
//	int OnChipIB_Width,OnChipIB_Height;
//
//	float I,P;
//	double latency;
//	int TmxTn;
//	//Tn=4;
//	//Tm=32;
//	//Tr=26;
//	//Tc=26;
//
//
//	//Tn=1;
//	//Tm=4;
//	//Tr=26;
//	//Tc=64;
//	//latency = design_space_explore(net, S, K, Tn, Tm, Tr, Tc,&Nma_total);
//	//printf("Nma_total=%d\n",Nma_total);
//	//P = ModelGOP/latency;
//	//I = ModelGOP*1000000000/Nma_total;
//	//printf("x=%d\n",x++);
//	//printf("Tn=%2d,Tm=%2d,Tr=%2d,Tc=%2d,I=%lf,P=%8.5lf,latency=%lf\n",Tn,Tm,Tr,Tc,I,P,latency);
//	////sprintf(line,"Tn=%2d,Tm=%2d,Tr=%2d,Tc=%2d,I=%lf,P=%8.5lf,flatency=%lf\n",Tn,Tm,Tr,Tc,I,P,latency);
//	////if(fputs(line,fp3)<0)fprintf(stderr,"write FILE failed\n");
//	time_t first, second; 
//	first=time(NULL);
//	for(Tn=1;Tn<=55;Tn++)
//	{
//		for(Tm=4;Tm<=180;Tm+=2)
//		{
//			TmxTn = Tn*Tm;
//			if(TmxTn<=180)
//			{
//				for(Tr=26;Tr<=208;Tr+=2)
//				{
//					for(Tc=26;Tc<=208;Tc+=2)
//					{
//						OnChipIB_Width  = ((Tc-1)*S+K);
//						OnChipIB_Height = ((Tr-1)*S+K);
//						Mem_in = ((int)ceil(OnChipIB_Width*OnChipIB_Height*16/18.0/1024))*Tn*2;
//						if((OnChipIB_Width*OnChipIB_Height*16/18.0/1024)<0.5)
//							Mem_in = 0;
//						Mem_out = ((int)ceil(Tr*Tc*16/18.0/1024))*Tm*2;
//						if((Tr*Tc*16/18.0/1024)<0.5)
//							Mem_out = 0;
//						Mem_inline = ((int)ceil(OnChipIB_Width*16/18.0/1024))*2;
//						Mem_outline = ((int)ceil(Tc*16/18.0/1024))*2;
//						Mem_wline = ((int)ceil(Tm*Tn*16/18.0/1024))*2;
//						Memory_total = Mem_in + Mem_out + Mem_inline + Mem_outline + Mem_wline;
//						if(Memory_total <= 280*0.85)
//						{
//							latency = design_space_explore(net, S, K, Tn, Tm, Tr, Tc,&Nma_total);
//							//printf("Nma_total=%d\n",Nma_total);
//							P = ModelGOP/latency;
//							I = ModelGOP*1000000000/Nma_total;
//							printf("x=%d\n",x++);
//							/*printf("Tn=%2d,Tm=%2d,Tr=%2d,Tc=%2d,I=%lf,P=%8.5lf,flatency=%lf\n",Tn,Tm,Tr,Tc,I,P,latency);*/
//							sprintf(line,"Tn=%2d,Tm=%2d,Tr=%2d,Tc=%2d,I=%.5lf,P=%.5lf,flatency=%lf\n",Tn,Tm,Tr,Tc,I,P,latency);
//							//sprintf(line,"%.5lf,%.5lf\n",I,P);
//							if(fputs(line,fp3)<0)fprintf(stderr,"write FILE failed\n");
//	
//						}
//					}
//				}
//			}
//		}
//	}
//	second=time(NULL);
//	printf("Explore in %f seconds.\n", difftime(second,first));
//	fclose(fp3);
//	
//	exit(0);
//
//
//}
//
////void yolov2_hls_ps(network *net, float *input)
////{
////	int x;
////
////	network orig = *net;
////	net->input = input;
////
////	float *region_buf = (float *)calloc(sizeof(float),13*13*425); 
////    network netp = *net;
////    int i;
////	int TR,TC,TM,TN;
////	int output_w,output_h;
////	int rLoops,cLoops,mLoops,nLoops;
////	double sum_gop = 0.0;
////
//////////////////eval start
////	int T2Rate,ColIncreaseLength;
////	int trow_loops;
////	int omLoops,orLoops;
////	const int Cin = 4;
////	const int Cout = 2;
////	const float freq = 150000000;
////	const int rw_fm_max_burstlength = 64;
////	const int r_wb_max_burstlength = 128;
////	float load_ifm,load_w,compute,store_ofm;
////	float load_w1,load_w2;
////	float store_o1,store_o2;
////	float load_ifm1,load_ifm2;
////	float layper_latency;
////	float inner_loop_latency;
////	float load_ifm_latency,load_w_latency,compute_latency,store_ofm_latency;
////	float load_ifm_latency_array[32];
////	float load_w_latency_array[32];
////	float compute_latency_array[32];
////	float store_ofm_latency_array[32];
////	float layper_latency_array[32];
////	int latency_cnt = 0;
////	int TRow;
////	int TCol;
//////////////////eval end
////
////    for(i = 0; i < netp.n; ++i)
////	{
////        netp.index = i;
////        layer l = netp.layers[i];
////		printf("Layer[%2d]: ",i);
////		switch(l.type)
////		{
////			case CONVOLUTIONAL:
////				printf("outputMemory:%8d;BN=%d;Activation=%d;conv  %5d %2d x%2d /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d  %5.3f BFLOPs\n",l.outputs,l.batch_normalize,l.activation, l.n, l.size, l.size, l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c, (2.0 * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w)/1000000000.);
////				sum_gop += (2.0 * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w)/1000000000.;
////				output_w = (l.w - l.size + 2*l.pad)/l.stride + 1 ;
////				output_h = (l.h - l.size + 2*l.pad)/l.stride + 1 ;
////
////				TR = MIN(((OnChipIB_Height-l.size)/l.stride+1),Tr);//keep Kernel_stride>=1
////				TR = MIN(output_h,TR);
////				TC = MIN(((OnChipIB_Width-l.size)/l.stride+1),Tc);
////				TC = MIN(output_w,TC);
////				TM = MIN(l.n,Tm);
////				TN = MIN(l.c,Tn);
////
////				rLoops = (int)ceil(((float)output_h)/TR);
////				cLoops = (int)ceil(((float)output_w)/TC);
////				mLoops = (int)ceil(((float)l.n)/TM);
////			    nLoops = (int)ceil(((float)l.c)/TN);
////			
////				TRow = (TR-1)*l.stride+l.size;
////				TCol = (TC-1)*l.stride+l.size;
////				switch(l.w)
////				{
////					case 26:
////						T2Rate = 2;
////						break;
////					case 13:
////						T2Rate = 4;
////						break;
////					default:
////						T2Rate = 1;
////						break;
////				}
////
////				load_ifm1 = 5/freq + mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
////				load_ifm2 = 5/freq + T2Rate*TCol/freq;
////				trow_loops = (int)ceil(((float)TRow/T2Rate));
////				load_ifm = 15/freq + load_ifm1 + load_ifm2 + (trow_loops-1)*MAX(load_ifm1,load_ifm2);
////
////				load_w1 = (Tm*Tn+10)/freq;
////				load_w2 = 5/freq + mm(TM*TN/2,r_wb_max_burstlength);
////				load_w = l.size*(load_w1 + load_w2 + (l.size-1)*MAX(load_w1,load_w2));
////
////				compute = (10 + l.size*l.size*TR*TC)/freq;
////
////				store_o1 = mm((TC == 26)?13:169,rw_fm_max_burstlength);
////				store_o2 = (5 + ((TC == 26)?26:2*13*13))/freq;
////
////				if(TM > Tm/2)
////				{
////					omLoops = Tm/2;
////				}else
////				{
////					omLoops = TM;
////				}
////
////				if(TC == 26)
////				{
////					orLoops = 26;
////				}else//TMxTRxTC TMx13x13 continues
////				{
////					orLoops = 1;
////					omLoops = omLoops/2;
////				}
////
////				store_ofm = (30)/freq + omLoops*(store_o1 + store_o2 + (orLoops-1)*MAX(store_o1,store_o2));
////
////				load_ifm_latency = rLoops*cLoops*mLoops*nLoops*load_ifm;
////				load_w_latency = rLoops*cLoops*mLoops*nLoops*load_w;
////				store_ofm_latency = rLoops*cLoops*mLoops*store_ofm;
////				compute_latency = rLoops*cLoops*mLoops*(nLoops*compute+TM/freq);
////				inner_loop_latency = ((nLoops-1)*MAX(MAX(load_ifm,load_w),compute)+MAX(load_ifm,load_w)+compute);
////				layper_latency = rLoops*cLoops*((mLoops-1)*MAX(inner_loop_latency,store_ofm)+inner_loop_latency+store_ofm);
////
////				load_ifm_latency_array[latency_cnt] = load_ifm_latency;
////				load_w_latency_array[latency_cnt] = load_w_latency;
////				compute_latency_array[latency_cnt] = compute_latency;
////				store_ofm_latency_array[latency_cnt] = store_ofm_latency;
////				layper_latency_array[latency_cnt] = layper_latency;
////				latency_cnt++;
////				printf("TR=%d,TC=%d,TM=%d,TN=%d,rLoops=%d,cLoops=%d,mLoops=%d,nLoops=%d\n",TR,TC,TM,TN,rLoops,cLoops,mLoops,nLoops);
////
////				break;
////			case MAXPOOL:
////				printf("outputMemory:%8d;max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n",l.outputs, l.size, l.size, l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c);
////				output_w = (l.w - l.size)/l.stride + 1 ;
////				output_h = (l.h - l.size)/l.stride + 1 ;
////				//output_w = l.out_h;
////				//output_h = l.out_w;
////
////				TR = MIN(((OnChipIB_Height-l.size)/l.stride+1),Tr);//keep Kernel_stride>=1
////				TC = MIN(((OnChipIB_Width-l.size)/l.stride+1),Tc);
////
////				TR = MIN(output_h,TR);
////				TC = MIN(output_w,TC);
////				TM = MIN(Tm,Tn);
////				TM = MIN(l.c,TM);
////				TN = TM;
////
////				rLoops = (int)ceil(((float)output_h)/TR);
////				cLoops = (int)ceil(((float)output_w)/TC);
////				mLoops = (int)ceil(((float)l.c)/TM);
////
////				TRow = (TR-1)*l.stride+l.size;
////				TCol = (TC-1)*l.stride+l.size;
////				switch(l.w)
////				{
////					case 26:
////						T2Rate = 2;
////						break;
////					case 13:
////						T2Rate = 4;
////						break;
////					default:
////						T2Rate = 1;
////						break;
////				}
////
////				load_ifm1 = 5/freq + mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
////				load_ifm2 = 5/freq + T2Rate*TCol/freq;
////				trow_loops = (int)ceil(((float)TRow/T2Rate));
////				load_ifm = 15/freq + load_ifm1 + load_ifm2 + (trow_loops-1)*MAX(load_ifm1,load_ifm2);
////
////				compute = (5 + l.size*l.size*TR*TC)/freq;
////
////				store_o1 = mm((TC == 26)?13:169,rw_fm_max_burstlength);
////				store_o2 = (5 + ((TC == 26)?26:2*13*13))/freq;
////
////				if(TM > Tm/2)
////				{
////					omLoops = Tm/2;
////				}else
////				{
////					omLoops = TM;
////				}
////
////				if(TC == 26)
////				{
////					orLoops = 26;
////				}else//TMxTRxTC TMx13x13 continues
////				{
////					orLoops = 1;
////					omLoops = omLoops/2;
////				}
////
////				store_ofm = (30)/freq + omLoops*(store_o1 + store_o2 + (orLoops-1)*MAX(store_o1,store_o2));
////
////				load_ifm_latency = rLoops*cLoops*mLoops*load_ifm;
////				store_ofm_latency = rLoops*cLoops*mLoops*store_ofm;
////				compute_latency = rLoops*cLoops*mLoops*compute;
////				/*layper_latency = rLoops*cLoops*((mLoops-1)*MAX(load_ifm,store_ofm)+ load_ifm + compute + store_ofm);*/
////				layper_latency = rLoops*cLoops*(mLoops*MAX(load_ifm,MAX(compute,store_ofm))+ load_ifm + store_ofm);
////
////				load_ifm_latency_array[latency_cnt] = load_ifm_latency;
////				load_w_latency_array[latency_cnt] = 0;
////				compute_latency_array[latency_cnt] = compute_latency;
////				store_ofm_latency_array[latency_cnt] = store_ofm_latency;
////				layper_latency_array[latency_cnt] = layper_latency;
////				latency_cnt++;
////
////				break;
////			case REORG:
////				printf("outputMemory:%8d;reorg              /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n",l.outputs,  l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c);			
////				output_w = 26;
////				output_h = 32*13;
////
////				TR = MIN(((OnChipIB_Height-l.stride)/l.stride+1),Tr);//keep Kernel_stride>=1
////				TR = MIN(output_h,TR);
////				TC = MIN(((OnChipIB_Width-l.stride)/l.stride+1),Tc);
////				TC = MIN(output_w,TC);
////				TM = 4;
////				TN = TM;
////
////				rLoops = (int)ceil(((float)output_h)/TR);
////				cLoops = (int)ceil(((float)output_w)/TC);
////				mLoops = 1;
////
////				TRow = (TR-1)*l.stride+l.stride;
////				TCol = (TC-1)*l.stride+l.stride;
////				switch(52)
////				{
////					case 26:
////						T2Rate = 2;
////						break;
////					case 13:
////						T2Rate = 4;
////						break;
////					default:
////						T2Rate = 1;
////						break;
////				}
////
////				load_ifm1 = 5/freq + mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
////				load_ifm2 = 5/freq + T2Rate*TCol/freq;
////				trow_loops = (int)ceil(((float)TRow/T2Rate));
////				load_ifm = 15/freq + load_ifm1 + load_ifm2 + (trow_loops-1)*MAX(load_ifm1,load_ifm2);
////
////				compute = (5 + l.stride*l.stride*TR*TC)/freq;
////
////				store_o1 = mm((TC == 26)?13:169,rw_fm_max_burstlength);
////				store_o2 = (5 + ((TC == 26)?26:2*13*13))/freq;
////
////				if(TM > Tm/2)
////				{
////					omLoops = Tm/2;
////				}else
////				{
////					omLoops = TM;
////				}
////
////				if(TC == 26)
////				{
////					orLoops = 26;
////				}else//TMxTRxTC TMx13x13 continues
////				{
////					orLoops = 1;
////					omLoops = omLoops/2;
////				}
////
////				store_ofm = (30)/freq + omLoops*(store_o1 + store_o2 + (orLoops-1)*MAX(store_o1,store_o2));
////
////				load_ifm_latency = rLoops*cLoops*mLoops*load_ifm;
////				store_ofm_latency = rLoops*cLoops*mLoops*store_ofm;
////				compute_latency = rLoops*cLoops*mLoops*compute;
////				//layper_latency = rLoops*cLoops*((mLoops-1)*MAX(load_ifm,store_ofm)+ load_ifm + compute + store_ofm);
////				layper_latency = rLoops*cLoops*(mLoops*MAX(load_ifm,MAX(compute,store_ofm))+ load_ifm + store_ofm);
////
////				load_ifm_latency_array[latency_cnt] = load_ifm_latency;
////				load_w_latency_array[latency_cnt] = 0;
////				compute_latency_array[latency_cnt] = compute_latency;
////				store_ofm_latency_array[latency_cnt] = store_ofm_latency;
////				layper_latency_array[latency_cnt] = layper_latency;
////				latency_cnt++;
////
////				break;
////			case ROUTE:
////				printf("outputMemory:%8d;route ",l.outputs);
////				int j;
////				for(j = 0; j < l.n; ++j){
////					printf(" %d", l.input_layers[j]);
////				}
////				printf("\n");
////				break;
////			case REGION:
////				printf("outputMemory:%8d;Detection\n",l.outputs);
////				netp.input = region_buf;
////				forward_region_layer(l,netp);
////				break;
////		}
////
////		netp.input = l.output;
////    }
////
////
////	//printf("SUM_GOP=%g\n",sum_gop);
////
////	//printf("latency_cnt=%d\n",latency_cnt);
////	//for(i=0;i<latency_cnt;i++)
////	//{
////	//	printf("[%d]:load=%.8lf store=%.8lf compute=%.8lf,total =%.8lf\n",
////	//	i,MAX(load_ifm_latency_array[i],load_w_latency_array[i]),store_ofm_latency_array[i],compute_latency_array[i],layper_latency_array[i]);
////	//}
////
////	//printf("load_latency:\n");
////	//for(i=0;i<latency_cnt;i++)
////	//{
////	//	printf("%.8lf\n",MAX(load_ifm_latency_array[i],load_w_latency_array[i]));
////	//}
////
////	//printf("compute_latency:\n");
////	//for(i=0;i<latency_cnt;i++)
////	//{
////	//	printf("%.8lf\n",compute_latency_array[i]);
////	//}
////
////	//printf("store_ofm_latency:\n");
////	//for(i=0;i<latency_cnt;i++)
////	//{
////	//	printf("%.8lf\n",store_ofm_latency_array[i]);
////	//}
////
////	//printf("layper_latency:\n");
////	//for(i=0;i<latency_cnt;i++)
////	//{
////	//	printf("%.8lf\n",layper_latency_array[i]);
////	//}
////
////	*net = orig;
////	free(region_buf);
////}
/////////////////////////////////////////////////////////////////////////20181229 reorg WeightQ BetaQ ok  InputQ ok end input opt ok input_g eval op1 //out4 gg (5)n4m32i4o2 ok //20190319 modify some bugs in output TR_MIN//for zynq7030 tiny-yolov2 20fps// 2019 3 28 explore design space



/////////////////////////////////////////////////////////////////////20181229 reorg WeightQ BetaQ ok  InputQ ok start input opt ok input_g eval op1 wuxiaoguo layer1 still 0.14s relu opt // input opt ok //output opt ok// wieght opt ok //out4 gg (5)n4m32i4o2 ok
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define S 2
#define K 3

#define Tn 4
#define Tm 48
#define Tr 26
#define Tc 52

#define OnChipIB_Width  ((Tc-1)*S+K)
#define OnChipIB_Height ((Tr-1)*S+K)
#define MAX_BETA_LENGTH (1024)
#define INTERWIDTH 20

typedef unsigned char UCHAR;

void mmcpy_inputport(int *input,int input_memcpy_buffer[(OnChipIB_Width+3)/2],int TN_MIN,int RowOffset,int RowIntNum)
{
	bool enable = TN_MIN > 0;
	if(!enable)
		return;

	memcpy(input_memcpy_buffer,(int *)(input + RowOffset),RowIntNum*sizeof(int));

}

void mmcpy_inputport1(int *input,int input_memcpy_buffer[(OnChipIB_Width+3)/2],int TN_MIN,int RowOffset,int RowIntNum)
{
	bool enable = TN_MIN > 1;
	if(!enable)
		return;

	memcpy(input_memcpy_buffer,(int *)(input + RowOffset),RowIntNum*sizeof(int));

}

void mmcpy_inputport2(int *input,int input_memcpy_buffer[(OnChipIB_Width+3)/2],int TN_MIN,int RowOffset,int RowIntNum)
{
	bool enable = TN_MIN > 2;
	if(!enable)
		return;

	memcpy(input_memcpy_buffer,(int *)(input + RowOffset),RowIntNum*sizeof(int));


}

void mmcpy_inputport3(int *input,int input_memcpy_buffer[(OnChipIB_Width+3)/2],int TN_MIN,int RowOffset,int RowIntNum)
{
	bool enable = TN_MIN > 3;
	if(!enable)
		return;

	memcpy(input_memcpy_buffer,(int *)(input + RowOffset),RowIntNum*sizeof(int));

}

void mmcpy_inputpixel_m2b_comb(int *input,int *input1,int *input2,int *input3,
						  int input_memcpy_buffer[(OnChipIB_Width+3)/2],int input_memcpy_buffer1[(OnChipIB_Width+3)/2],
						  int input_memcpy_buffer2[(OnChipIB_Width+3)/2],int input_memcpy_buffer3[(OnChipIB_Width+3)/2],
						  char RowBeginByte[Tn],int TN_MIN,int t2,int RowSub,int IN_OFFSET,int RowIncreaseLength,int IHxIW,int ColIncreaseLength,int next_t2[1],bool next_IsRowPixel[1],bool IsRowPixel,bool enable)
{
	static int tmp_inoffset;

	next_t2[0] = t2;
	next_IsRowPixel[0] = IsRowPixel;

	if(!enable)
		return;

	bool init = (t2==0);
	if(init)
	{
		tmp_inoffset = IN_OFFSET;
	}else
	{
		tmp_inoffset += RowIncreaseLength;
	}

	int InOffset[Tn];
	int RowOffset[Tn];
	char LowBit[Tn];
	int BeginByteNum[Tn];
	int RowIntNum[Tn];

	int t1;
	for(t1 = 0;t1 < Tn;t1++)
	{
		InOffset[t1] = tmp_inoffset + t1*IHxIW;
		RowOffset[t1] = InOffset[t1] >> 1;
		LowBit[t1] = InOffset[t1]&0x1;
		RowBeginByte[t1] = LowBit[t1];
		BeginByteNum[t1] = ColIncreaseLength + LowBit[t1];

		assert((BeginByteNum[t1] > 0)&&(BeginByteNum[t1] < 256));

		RowIntNum[t1] = BeginByteNum[t1] >> 1;
		if(BeginByteNum[t1]&0x1)
			RowIntNum[t1]++;

		assert((RowIntNum[t1] > 0)&&(RowIntNum[t1] < 256));
	}

	mmcpy_inputport(input,input_memcpy_buffer, TN_MIN,RowOffset[0],RowIntNum[0]);
	mmcpy_inputport1(input1,input_memcpy_buffer1, TN_MIN,RowOffset[1],RowIntNum[1]);
	mmcpy_inputport2(input2,input_memcpy_buffer2, TN_MIN,RowOffset[2],RowIntNum[2]);
	mmcpy_inputport3(input3,input_memcpy_buffer3, TN_MIN,RowOffset[3],RowIntNum[3]);
}

void copy_input2buf_row(short input_buffer[Tn][OnChipIB_Height][OnChipIB_Width],int Input_w,int TN_MIN,int row_len,int col_len,int RowSub,int ColSub,
					int input_memcpy_buffer[(OnChipIB_Width+3)/2],int input_memcpy_buffer1[(OnChipIB_Width+3)/2],
					int input_memcpy_buffer2[(OnChipIB_Width+3)/2],int input_memcpy_buffer3[(OnChipIB_Width+3)/2],
					char RowBeginByte[Tn],UCHAR TRow,UCHAR TCol,int LayerType,int next_t2[1],bool next_enable[1],bool enable,int T2Rate)
{

	if(!enable)
		return;

	static int t2_local = 0;
	int t2 = next_t2[0];
	bool IsRowPixel = next_enable[0];
	int t1,t3;
	int t2r,T2R;

	bool initial = (t2==0);
	if(initial)
	{
		t2_local = 0;
	}

	short pad_value = 0;
	if(LayerType==1)
		pad_value = 0x8001;

	assert(TN_MIN < 8);//xx8
	assert(row_len < 256);
	assert(col_len < 256);
	assert( (RowSub == 1)||(RowSub == 0));
	assert( (ColSub == 1)||(ColSub == 0));

	int input_mmcpy_offset[Tn];
	bool NextInputFlag[Tn];
	char cnt[Tn];
	short input_array[Tn][2];

	for(t1 = 0;t1 < Tn; t1++)
	{
		input_mmcpy_offset[t1] = 0;
	}

	if(!IsRowPixel)
	{
		T2R = T2Rate + 1;
	}else
	{
		T2R = T2Rate;
	}
	int T2R_bound = MIN(t2_local + T2R,OnChipIB_Height);

	bool IsRowInit_flag = true;

	for(t2r = t2_local;t2r < T2R_bound; t2r++)
		for(t3 = 0;t3 < TCol; t3++)
		{
			bool IsRowPixel_t2r = (t2r >= RowSub)&&(t2r < (row_len + RowSub));
			bool IsColPixel = (t3 >= ColSub)&&(t3 < (col_len + ColSub));
			bool IsRowInit = (t3==ColSub)&&IsRowInit_flag;

			if(IsRowPixel_t2r&&IsColPixel)
			{
				if(IsRowInit)
				{
					IsRowInit_flag = false;
					cnt[0] = RowBeginByte[0];
					cnt[1] = RowBeginByte[1];
					cnt[2] = RowBeginByte[2];
					cnt[3] = RowBeginByte[3];
					NextInputFlag[0] = true;
					NextInputFlag[1] = true;
					NextInputFlag[2] = true;
					NextInputFlag[3] = true;
				}

				if(NextInputFlag[0])
				{
					input_array[0][0] = input_memcpy_buffer[input_mmcpy_offset[0]];
					input_array[0][1] = input_memcpy_buffer[input_mmcpy_offset[0]] >> 16;
					input_mmcpy_offset[0]++;
					NextInputFlag[0] = false;
				}

				if(NextInputFlag[1])
				{
					input_array[1][0] = input_memcpy_buffer1[input_mmcpy_offset[1]];
					input_array[1][1] = input_memcpy_buffer1[input_mmcpy_offset[1]] >> 16;
					input_mmcpy_offset[1]++;
					NextInputFlag[1] = false;
				}

				if(NextInputFlag[2])
				{
					input_array[2][0] = input_memcpy_buffer2[input_mmcpy_offset[2]];
					input_array[2][1] = input_memcpy_buffer2[input_mmcpy_offset[2]] >> 16;
					input_mmcpy_offset[2]++;
					NextInputFlag[2] = false;
				}

				if(NextInputFlag[3])
				{
					input_array[3][0] = input_memcpy_buffer3[input_mmcpy_offset[3]];
					input_array[3][1] = input_memcpy_buffer3[input_mmcpy_offset[3]] >> 16;
					input_mmcpy_offset[3]++;
					NextInputFlag[3] = false;
				}

				input_buffer[0][t2r][t3] = input_array[0][cnt[0]];
				input_buffer[1][t2r][t3] = input_array[1][cnt[1]];
				input_buffer[2][t2r][t3] = input_array[2][cnt[2]];
				input_buffer[3][t2r][t3] = input_array[3][cnt[3]];

				if(cnt[0]==1)
				{
					NextInputFlag[0] = true;
					cnt[0] = 0;
				}else
				{
					cnt[0] = 1;
				}

				if(cnt[1]==1)
				{
					NextInputFlag[1] = true;
					cnt[1] = 0;
				}else
				{
					cnt[1] = 1;
				}

				if(cnt[2]==1)
				{
					NextInputFlag[2] = true;
					cnt[2] = 0;
				}else
				{
					cnt[2] = 1;
				}

				if(cnt[3]==1)
				{
					NextInputFlag[3] = true;
					cnt[3] = 0;
				}else
				{
					cnt[3] = 1;
				}
			}else
			{
				input_buffer[0][t2r][t3] = pad_value;
				input_buffer[1][t2r][t3] = pad_value;
				input_buffer[2][t2r][t3] = pad_value;
				input_buffer[3][t2r][t3] = pad_value;
			}

		}

		t2_local += T2R;
}

void input_load(int *input,int *input1,int *input2,int *input3,
				short input_buffer[Tn][OnChipIB_Height][OnChipIB_Width],int r,int c,int n,int Kernel_stride,int Padding,UCHAR TRow,UCHAR TCol,int Input_w,int Input_h,int TN_MIN,int IHxIW,int LayerType)
{
	int RowSub,ColSub;

	static int input_memcpy_buffer0[(OnChipIB_Width+3)/2];
	static int input_memcpy_buffer1[(OnChipIB_Width+3)/2];
	static int input_memcpy_buffer2[(OnChipIB_Width+3)/2];
	static int input_memcpy_buffer3[(OnChipIB_Width+3)/2];
	char RowBeginByte[Tn];//0 ro 1

	static int input_memcpy_buffer02[(OnChipIB_Width+3)/2];
	static int input_memcpy_buffer12[(OnChipIB_Width+3)/2];
	static int input_memcpy_buffer22[(OnChipIB_Width+3)/2];
	static int input_memcpy_buffer32[(OnChipIB_Width+3)/2];
	char RowBeginByte2[Tn];//0 ro 1


	int t1,t2,t3,t4;

	assert(r < 512);
	assert(c < 512);
	assert(n < 2048);//gg1280
	assert(Kernel_stride < 4);
	assert(Padding < 2);
	assert(Input_w < 512);
	assert(Input_h < 1024);//gg
	assert(TN_MIN < 8);//xx8
	assert(IHxIW < 512*512);

	const int Coffset = c*Kernel_stride - Padding;
	const int Roffset = r*Kernel_stride - Padding;

	assert( (Coffset >= -1) && (Coffset < 1024));
	assert( (Roffset >= -1) && (Roffset < 1024));

	int TRow_top,TRow_bottom;
	int TCol_left,TCol_right;
	int row_len,col_len;

	if(Coffset > 0)
		TCol_left = Coffset;
	else
		TCol_left = 0;

	if((Coffset + TCol-1)<Input_w)
		TCol_right = Coffset + TCol;
	else
		TCol_right = Input_w;

	col_len = TCol_right - TCol_left;

	if(Roffset > 0)
		TRow_top = Roffset;
	else
		TRow_top = 0;

	if((Roffset + TRow-1)<Input_h)
		TRow_bottom = Roffset + TRow;
	else
		TRow_bottom = Input_h;

	row_len = TRow_bottom - TRow_top;

	assert( (TRow_bottom > 0) && (TRow_bottom < 2048));
	assert( (TCol_right > 0) && (TCol_right < 2048));

	assert(row_len < 64);
	assert(col_len < 128);

	int IN_OFFSET = n*IHxIW + TRow_top*Input_w +TCol_left;

	int RowIncreaseLength;
	int ColIncreaseLength;
	int T2Rate;
	switch(Input_w)
	{
		case 26:
			RowIncreaseLength = 2*Input_w;
			ColIncreaseLength = 2*Input_w;
			T2Rate = 2;
			break;
		case 13:
			RowIncreaseLength = 4*Input_w;
			ColIncreaseLength = 4*Input_w;
			T2Rate = 4;
			break;
		default:
			RowIncreaseLength = Input_w;
			ColIncreaseLength = col_len;
			T2Rate = 1;
			break;
	}

	//assert(ColNum < 64*64);
	//assert(RowNum < 64);

	bool pingpong = 1;

	RowSub = TRow_top - Roffset;
	ColSub = TCol_left - Coffset;

	int next_t2[1];
	bool next_IsRowPixel[1];

	int next_t22[1];
	bool next_IsRowPixel2[1];

	//for(t2 = 0;t2 < TRow; t2 += T2Rate)
	//{
	//	bool IsRowPixel = (t2 >= RowSub)&&(t2 < (row_len + RowSub));

	//	mmcpy_inputpixel_m2b_comb(input,input1,input2,input3,
	//						input_memcpy_buffer0, input_memcpy_buffer1,
	//						input_memcpy_buffer2, input_memcpy_buffer3,
	//						RowBeginByte, TN_MIN, t2, RowSub, IN_OFFSET, RowIncreaseLength, IHxIW, ColIncreaseLength, next_t2,next_IsRowPixel,IsRowPixel,true);

	//	copy_input2buf_row( input_buffer, Input_w, TN_MIN, row_len, col_len, RowSub, ColSub,
	//					input_memcpy_buffer0, input_memcpy_buffer1,
	//					input_memcpy_buffer2, input_memcpy_buffer3,
	//				RowBeginByte, TRow, TCol,LayerType,next_t2,next_IsRowPixel,true,T2Rate);
	//}

	int trow_loops = (int)ceil(((float)TRow/T2Rate));
	int TMP_t2;

	for(TMP_t2 = 0,t2 = 0;TMP_t2 < trow_loops + 1; t2 += T2Rate,TMP_t2++)
	{
		bool IsRowPixel = (t2 >= RowSub)&&(t2 < (row_len + RowSub));

		if(pingpong == 1)
		{
			mmcpy_inputpixel_m2b_comb(input,input1,input2,input3,
							   input_memcpy_buffer0, input_memcpy_buffer1,
							   input_memcpy_buffer2, input_memcpy_buffer3,
							   RowBeginByte, TN_MIN, t2, RowSub, IN_OFFSET, RowIncreaseLength, IHxIW, ColIncreaseLength, next_t2,next_IsRowPixel,IsRowPixel,TMP_t2!=trow_loops);

			copy_input2buf_row( input_buffer, Input_w, TN_MIN, row_len, col_len, RowSub, ColSub,
						 input_memcpy_buffer02, input_memcpy_buffer12,input_memcpy_buffer22, input_memcpy_buffer32,
						RowBeginByte2, TRow, TCol,LayerType,next_t22,next_IsRowPixel2,TMP_t2!=0,T2Rate);
			pingpong = 0;
		}else
		{
			mmcpy_inputpixel_m2b_comb(input,input1,input2,input3,
							   input_memcpy_buffer02, input_memcpy_buffer12,
							   input_memcpy_buffer22, input_memcpy_buffer32,
							   RowBeginByte2, TN_MIN, t2, RowSub, IN_OFFSET, RowIncreaseLength, IHxIW, ColIncreaseLength, next_t22,next_IsRowPixel2,IsRowPixel,TMP_t2!=trow_loops);

			copy_input2buf_row( input_buffer, Input_w, TN_MIN, row_len, col_len, RowSub, ColSub,
						 input_memcpy_buffer0, input_memcpy_buffer1,input_memcpy_buffer2, input_memcpy_buffer3,
						RowBeginByte, TRow, TCol,LayerType,next_t2,next_IsRowPixel,TMP_t2!=0,T2Rate);
			pingpong = 1;
		}
	}

	assert(TRow_top < 1024);
	assert(TCol_left < 1024);

}

//void weight_load_reorg(int *Weight,short weight_buffer[Tm][Tn][K][K],bool weight_load_enable,int m,int n,int IFM_numxKxK,int KxK,int Kernel_size,int TM_MIN,int TN_MIN)
//{
//	int t1,t2,t3,t4;
//	static int weight_memcpy_buffer[Tm*Tn*K*K/2];
//	static int Woffset;
//
//	if(!weight_load_enable)
//		return;
//
//	assert(m < 1024);
//	assert(n < 2048);//gg2048
//	assert(IFM_numxKxK < 1024*16);
//	assert(Kernel_size < 4);
//	assert(TM_MIN < 64);
//	assert(TN_MIN < 8);//xx8
//
//	if(m==0&&n==0)
//		Woffset = 0;
//	if((TM_MIN*TN_MIN*KxK)%2)
//		printf("weight % error\n");
//
//	unsigned int ReadLength = (TM_MIN*TN_MIN*KxK)>>1;
//	memcpy(weight_memcpy_buffer,(int *)(Weight + Woffset),ReadLength*sizeof(int));
//	Woffset += ReadLength;
//	
//	int weight_memcpy_offset = 0;
//	unsigned char cnt = 0;
//	short input_array[2];
//	short input_value;
//	for(t1 = 0;t1 < Tm; t1++)
//		for(t2 = 0;t2 < Tn; t2++)
//			for(t3 = 0;t3 <Kernel_size; t3++)
//				for(t4 = 0;t4 <Kernel_size; t4++)
//				{
//					bool Enable = (t1 < TM_MIN)&&(t2 < TN_MIN);
//					if(Enable)
//					{
//						if(cnt==0)
//						{
//							input_array[0] = weight_memcpy_buffer[weight_memcpy_offset];
//							input_array[1] = weight_memcpy_buffer[weight_memcpy_offset] >> 16;
//							weight_memcpy_offset++;
//						}
//
//						input_value = input_array[cnt];
//						weight_buffer[t1][t2][t3][t4] =  input_value;
//
//						cnt++;						
//						if(cnt==2)
//							cnt = 0;
//					}
//					else
//						weight_buffer[t1][t2][t3][t4] = 0;
//				}	
//}

void weight_mmcpy_everyKxK(int *Weight,int weight_memcpy_buffer[Tm*Tn/2],int t3,int t4,int next_t3[1],int next_t4[1],unsigned int ReadLength,bool init_enable,bool enable)
{
	if(!enable)
		return;

	static int Woffset;
	next_t3[0] = t3;
	next_t4[0] = t4;

	if(init_enable)
	{
		Woffset = 0;
	}

	memcpy(weight_memcpy_buffer,(int *)(Weight + Woffset),ReadLength*sizeof(int));
	Woffset += ReadLength;
}

void load_weight2buf_everyKxK(int weight_memcpy_buffer[Tm*Tn/2],short weight_buffer[Tm][Tn][K][K],int t3,int t4,int TM_MIN,int TN_MIN,bool enable)
{

	if(!enable)
		return;

	int t1,t2;
	int weight_memcpy_offset = 0;
	unsigned char cnt = 0;
	short input_array[2];
	short input_value;

	for(t1 = 0;t1 < Tm; t1++)
		for(t2 = 0;t2 < Tn; t2++)
		{
			bool Enable = (t1 < TM_MIN)&&(t2 < TN_MIN);
			if(Enable)
			{
				if(cnt==0)
				{
					input_array[0] = weight_memcpy_buffer[weight_memcpy_offset];
					input_array[1] = weight_memcpy_buffer[weight_memcpy_offset] >> 16;
					weight_memcpy_offset++;
				}
				input_value = input_array[cnt];

				cnt++;						
				if(cnt==2)
					cnt = 0;
			}
			else
				input_value = 0;

			weight_buffer[t1][t2][t3][t4] =  input_value;
		}	
}

void weight_load_reorg(int *Weight,short weight_buffer[Tm][Tn][K][K],bool weight_load_enable,int m,int n,int IFM_numxKxK,int KxK,int Kernel_size,int TM_MIN,int TN_MIN)
{
	/*int t1,t2,t3,t4;*/
	static int weight_memcpy_buffer[Tm*Tn/2];
	static int weight_memcpy_buffer1[Tm*Tn/2];

	if(!weight_load_enable)
		return;

	assert(m < 1024);
	assert(n < 2048);//gg2048
	assert(IFM_numxKxK < 1024*16);
	assert(Kernel_size < 4);
	assert(TM_MIN < 128);
	assert(TN_MIN < 8);//xx8

	bool Me0aNe0 = (m==0)&&(n==0);
	unsigned int ReadLength = (TM_MIN*TN_MIN)>>1;

	if((TM_MIN*TN_MIN)%2)
		printf("weight % error\n");

	int t3,t4;
	int next_t3[1];
	int next_t4[1];
	int next_t31[1];
	int next_t41[1];

	bool pingpong = true;
	for(t3 = 0;t3 < Kernel_size;t3++)
		for(t4 = 0;t4 < Kernel_size + 1;t4++)
		{
			if(pingpong)
			{
				weight_mmcpy_everyKxK(Weight, weight_memcpy_buffer, t3, t4,next_t3,next_t4, ReadLength,Me0aNe0&&(t3==0)&&(t4==0),t4!=Kernel_size);
				load_weight2buf_everyKxK(weight_memcpy_buffer1, weight_buffer, next_t31[0], next_t41[0], TM_MIN, TN_MIN,t4!=0);
				pingpong = false;
			}else
			{
				weight_mmcpy_everyKxK(Weight, weight_memcpy_buffer1, t3, t4,next_t31,next_t41, ReadLength,Me0aNe0&&(t3==0)&&(t4==0),t4!=Kernel_size);
				load_weight2buf_everyKxK(weight_memcpy_buffer, weight_buffer, next_t3[0], next_t4[0], TM_MIN, TN_MIN,t4!=0);
				pingpong = true;
			}
		}

}

void copy_input_weight(int *input,int *input1,int *input2,int *input3,int *Weight,int InFM_num,int Input_w,int Input_h,int OutFM_num,int Kernel_size,int Kernel_stride,int r,int c,int m,int n,
		int TM_MIN,int TN,UCHAR TRow,UCHAR TCol,int Padding,short input_buffer[Tn][OnChipIB_Height][OnChipIB_Width],short weight_buffer[Tm][Tn][K][K],int TMP_N_next[1],
		bool enable,bool weight_load_enable,const int IHxIW,const int KxK,const int IFM_numxKxK,const int LayerType)
{
	if(!enable)
		return ;

	const int TN_MIN = MIN(TN,InFM_num - n);
	TMP_N_next[0] = n;

	input_load(input,input1,input2,input3, input_buffer, r, c, n, Kernel_stride, Padding, TRow, TCol, Input_w, Input_h, TN_MIN, IHxIW, LayerType);
	weight_load_reorg(Weight,weight_buffer,weight_load_enable,m,n,IFM_numxKxK,KxK,Kernel_size,TM_MIN,TN_MIN);

}
//////////////////////////////////////////////////T3 end
void copy_local_beta(short beta_buffer[MAX_BETA_LENGTH],short local_beta_buffer[MAX_BETA_LENGTH],const int TM_MIN,int m)
{
	int offset;
	int tm;
	for(tm = 0,offset = m;tm < TM_MIN;tm++)
	{
		local_beta_buffer[tm] = beta_buffer[offset];
		offset++;
	}
}

void compute(short input_buffer[Tn][OnChipIB_Height][OnChipIB_Width],int output_buffer[Tm][Tr][Tc],
		short weight_buffer[Tm][Tn][K][K],short beta_buffer[MAX_BETA_LENGTH],int TMP_N_next,
		const int Kernel_size,const int Kernel_stride,int TMP_M,
		const int TM_MIN,const int TR_MIN,const int TC_MIN,bool enable,bool copy_beta_enable,bool IsNL,bool reluenable,
		UCHAR InterSubBeta,UCHAR WeightAddInputSubInter,UCHAR InterSubOutput)
{

	static short local_beta_buffer[Tm];
#pragma HLS ARRAY_PARTITION variable=local_beta_buffer complete dim=1

//	static int compute_buffer[Tm][Tr][Tc];
//#pragma HLS ARRAY_PARTITION variable=compute_buffer complete dim=1

	if(!enable)
	{
		return;
	}

	if(copy_beta_enable)
	{
		copy_local_beta(beta_buffer,local_beta_buffer,TM_MIN,TMP_M);
	}

	int partial_mul[Tm][Tn];
#pragma HLS ARRAY_PARTITION variable=partial_mul complete dim=1
#pragma HLS ARRAY_PARTITION variable=partial_mul complete dim=2

	unsigned char i,j,tr,tc,tm,tn;
	unsigned char Kernel_size_8b = Kernel_size;
	unsigned char TR_MIN_8b = TR_MIN;
	unsigned char TC_MIN_8b = TC_MIN;

	assert(InterSubBeta < 16);
	assert(WeightAddInputSubInter < 16);
	assert(InterSubOutput < 16);

	assert(Kernel_size < 4);
	assert(TR_MIN < 32);
	assert(TC_MIN < 64);

	int n = TMP_N_next;
	assert(n < 2048);//gg1280

	for(i = 0;i < Kernel_size_8b; i++)
		for(j = 0;j < Kernel_size_8b; j++)
			for(tr = 0;tr < TR_MIN_8b;tr++)
				for(tc = 0;tc < TC_MIN_8b;tc++)
				{
#pragma HLS PIPELINE
					for(tm = 0;tm < Tm;tm++)
					{
#pragma HLS DEPENDENCE variable=compute_buffer inter false
						int tmp_add_result;
						if(i==0&&j==0&&n==0)
						{
							tmp_add_result = local_beta_buffer[tm] << InterSubBeta;
						}
						else
							tmp_add_result = output_buffer[tm][tr][tc];

						partial_mul[tm][0] = (weight_buffer[tm][0][i][j]*input_buffer[0][tr+i][tc+j]) >> WeightAddInputSubInter;//Q1+Q2-Q3
						partial_mul[tm][1] = (weight_buffer[tm][1][i][j]*input_buffer[1][tr+i][tc+j]) >> WeightAddInputSubInter;//Q1+Q2-Q3
						partial_mul[tm][2] = (weight_buffer[tm][2][i][j]*input_buffer[2][tr+i][tc+j]) >> WeightAddInputSubInter;//Q1+Q2-Q3
						partial_mul[tm][3] = (weight_buffer[tm][3][i][j]*input_buffer[3][tr+i][tc+j]) >> WeightAddInputSubInter;//Q1+Q2-Q3

						int tmp_add1 = partial_mul[tm][0] + partial_mul[tm][1];
						int tmp_add2 = partial_mul[tm][2] + partial_mul[tm][3];
						int tmp_add12 = tmp_add1 + tmp_add2;
						output_buffer[tm][tr][tc] = tmp_add_result + tmp_add12;
					}
				}
}

////////////////version-0.3 start o4 gg
//void mmcpy_outputport(int *Output,int output_tmp[Tr*Tc/4],int tm,int mLoop,int OutputOffset,int OutputLength)
//{
//	bool enable = tm < mLoop;
//	if(!enable)
//		return;
//
//	memcpy((int *)(Output + OutputOffset),(int *)(output_tmp),OutputLength*sizeof(int));
//}
//
//void mmcpy_outputport1(int *Output,int output_tmp[Tr*Tc/4],int tm,int mLoop,int OutputOffset,int OutputLength)
//{
//	bool enable = tm < mLoop;
//	if(!enable)
//		return;
//
//	memcpy((int *)(Output + OutputOffset),(int *)(output_tmp),OutputLength*sizeof(int));
//}
//
//void mmcpy_outputport2(int *Output,int output_tmp[Tr*Tc/4],int tm,int mLoop,int OutputOffset,int OutputLength)
//{
//	bool enable = tm < mLoop;
//	if(!enable)
//		return;
//
//	memcpy((int *)(Output + OutputOffset),(int *)(output_tmp),OutputLength*sizeof(int));
//}
//
//void mmcpy_outputport3(int *Output,int output_tmp[Tr*Tc/4],int tm,int mLoop,int OutputOffset,int OutputLength)
//{
//	bool enable = tm < mLoop;
//	if(!enable)
//		return;
//
//	memcpy((int *)(Output + OutputOffset),(int *)(output_tmp),OutputLength*sizeof(int));
//}
//
//void mmcpy_outputpixel(int *Output,int *Output1,int *Output2,int *Output3,int output_tmp[Tr*Tc/4],int output_tmp1[Tr*Tc/4],int output_tmp2[Tr*Tc/4],int output_tmp3[Tr*Tc/4],
//					   int tm,int mLoop1,int mLoop2,int mLoop3,int mLoop4,int outputoffsetarray[2],int OutputLength,bool enable)
//{
//	if(!enable)
//	{
//		return;
//	}
//	mmcpy_outputport( Output  ,output_tmp ,tm,mLoop1,outputoffsetarray[0],OutputLength);
//	mmcpy_outputport1(Output1 ,output_tmp1,tm,mLoop2,outputoffsetarray[1],OutputLength);
//	mmcpy_outputport2(Output2 ,output_tmp2,tm,mLoop3,outputoffsetarray[2],OutputLength);
//	mmcpy_outputport3(Output3 ,output_tmp3,tm,mLoop4,outputoffsetarray[3],OutputLength);
//}
//
//void outputpixel2buf(int output_buffer[Tm][Tr][Tc],int output_tmp[Tr*Tc/4],int output_tmp1[Tr*Tc/4],int output_tmp2[Tr*Tc/4],int output_tmp3[Tr*Tc/4],
//					 bool IsNL,int InterSubOutput,int LayerType,bool TC_MINe26,int TR_MIN,int TC_MIN,int mLoop,int rLoop, bool init,
//					 int outputoffsetarray[Tn],int OutputOffset1_sum,int OutputOffset1_sum1,int OutputOffset1_sum2,int OutputOffset1_sum3,int OutputOffset2_sum,int tm_next[1],bool enable)
//{
//	static int tm;
//	int tmp_output0,tmp_output1,tmp_output2,tmp_output3;
//	short tmp_output20,tmp_output21,tmp_output22,tmp_output23;
//	short ouput_array0,ouput_array1,ouput_array2,ouput_array3;
//	int tmp0,tmp1,tmp2,tmp3;
//	UCHAR outputoffset;
//	int tr,tc,tm_count,tr_count;
//	UCHAR cnt;
//	int TM_LOOP,TR_LOOP;
//	int i;
//
//	if(!enable)
//	{
//		return;
//	}
//
//	tm_next[0] =  mLoop;
//
//	assert( (InterSubOutput < 16)&&(InterSubOutput > 0));
//
//	if(init)
//	{
//		tm = 0;
//	}
//
//	if(TC_MINe26)
//	{
//		tm = mLoop;
//		tr = rLoop;
//		TM_LOOP = 1;
//		TR_LOOP = 1;
//	}else
//	{
//		tr = 0;
//		TM_LOOP = 2;
//		TR_LOOP = 13;
//	}
//
//	outputoffset  = 0;
//	cnt = 0;
//	for(tm_count = 0;tm_count < TM_LOOP;tm_count++,tm++,tr = 0)
//		for(tr_count = 0;tr_count < TR_LOOP;tr_count++,tr++)
//			for(tc = 0;tc < TC_MIN;tc++)
//			{
//				tmp0  = output_buffer[tm][tr][tc];
//				tmp1  = output_buffer[tm + 8][tr][tc];
//				tmp2  = output_buffer[tm + 2*8][tr][tc];
//				tmp3  = output_buffer[tm + 3*8][tr][tc];
//				
//				if(IsNL&&(tmp0 < 0))
//				{
//					tmp_output0 = ((long long)tmp0*0xccc)>>15;
//				}else
//				{
//					tmp_output0 = tmp0;
//				}
//
//				if(IsNL&&(tmp1 < 0))
//				{
//					tmp_output1 = ((long long)tmp1*0xccc)>>15;
//				}else
//				{
//					tmp_output1 = tmp1;
//				}
//
//				if(IsNL&&(tmp2 < 0))
//				{
//					tmp_output2 = ((long long)tmp2*0xccc)>>15;
//				}else
//				{
//					tmp_output2 = tmp2;
//				}
//
//				if(IsNL&&(tmp3 < 0))
//				{
//					tmp_output3 = ((long long)tmp3*0xccc)>>15;
//				}else
//				{
//					tmp_output3 = tmp3;
//				}
//
//				if(LayerType==0)
//				{
//					tmp_output20 = tmp_output0 >> InterSubOutput;
//					tmp_output21 = tmp_output1 >> InterSubOutput;
//					tmp_output22 = tmp_output2 >> InterSubOutput;
//					tmp_output23 = tmp_output3 >> InterSubOutput;
//				}
//				else
//				{
//					tmp_output20 = tmp_output0;
//					tmp_output21 = tmp_output1;
//					tmp_output22 = tmp_output2;
//					tmp_output23 = tmp_output3;
//				}				
//
//				if(cnt==1)
//				{
//					output_tmp[outputoffset]  = (ouput_array0 &0x0000FFFF) | ((tmp_output20 << 16 )&0xFFFF0000);
//					output_tmp1[outputoffset] = (ouput_array1 &0x0000FFFF) | ((tmp_output21 << 16 )&0xFFFF0000);
//					output_tmp2[outputoffset] = (ouput_array2 &0x0000FFFF) | ((tmp_output22 << 16 )&0xFFFF0000);
//					output_tmp3[outputoffset] = (ouput_array3 &0x0000FFFF) | ((tmp_output23 << 16 )&0xFFFF0000);
//					outputoffset++;
//					cnt = 0;
//				}else
//				{
//					ouput_array0 = tmp_output20;
//					ouput_array1 = tmp_output21;
//					ouput_array2 = tmp_output22;
//					ouput_array3 = tmp_output23;
//					cnt = 1;
//				}
//			}
//
//	assert( TC_MIN < 32);
//	assert( tr < 32);
//	assert( tm < 10);
//
//	outputoffsetarray[0] = (OutputOffset1_sum  + OutputOffset2_sum)>>1;
//	outputoffsetarray[1] = (OutputOffset1_sum1 + OutputOffset2_sum)>>1;	
//	outputoffsetarray[2] = (OutputOffset1_sum2 + OutputOffset2_sum)>>1;
//	outputoffsetarray[3] = (OutputOffset1_sum3 + OutputOffset2_sum)>>1;	
//
//}
//
//void write_back_output_reorg(int output_buffer[Tm][Tr][Tc],int *Output,int r,int c,int m,const int Output_w,const int Output_h,
//					   const int TM_MIN,const int TR_MIN,const int TC_MIN,const int OHxOW,bool write_flag,const int OutputQ,bool IsNL,int InterSubOutput,int LayerType)
//{
//	static int output_tmp00[Tr*Tc/4];
//	static int output_tmp01[Tr*Tc/4];
//	static int output_tmp02[Tr*Tc/4];
//	static int output_tmp03[Tr*Tc/4];
//
//	static int output_tmp10[Tr*Tc/4];
//	static int output_tmp11[Tr*Tc/4];
//	static int output_tmp12[Tr*Tc/4];
//	static int output_tmp13[Tr*Tc/4];
//
//	int tr,tm,tc;
//	int OutputLength;
//	int mLoopc,mLoop,mLoop1,mLoop2,mLoop3,mLoop4,rLoop;
//
//	if(!write_flag)
//		return;
//
//	assert(TM_MIN < 64);
//	assert(TR_MIN < 32);
//	assert(TC_MIN < 32);
//
//	assert(m < 1024);
//	assert(r < 512);
//	assert(c < 512);
//	assert(OHxOW < 512*512);
//	assert(Output_w < 512);
//
//	unsigned char TM_MIN_g;
//	if(TM_MIN==9)
//		TM_MIN_g = 12;
//	else
//		TM_MIN_g = TM_MIN;
//
//	const int offset = m*OHxOW + r*Output_w + c;
//
//	bool mLoop1enable = true;
//	bool mLoop2enable = TM_MIN_g > 7;
//	bool mLoop3enable = TM_MIN_g > 15;
//	bool mLoop4enable = TM_MIN_g > 23;
//
//	bool TC_MINe26 = TC_MIN == 26;
//
//	if(mLoop2enable)
//	{
//		mLoop = 8;
//		mLoop1 = 8;
//		if(mLoop3enable)
//		{
//			mLoop2 = 8;
//			if(mLoop4enable)
//			{
//				mLoop3 = 8;
//				mLoop4 = TM_MIN_g - 24;
//			}
//			else
//			{
//				mLoop3 = TM_MIN_g - 16;
//				mLoop4 = 0;
//			}
//		}else
//		{
//			mLoop2 = TM_MIN_g - 8;
//			mLoop3 = 0;
//			mLoop4 = 0;
//		}
//	}else
//	{
//		mLoop = TM_MIN_g;
//		mLoop1 = TM_MIN_g;
//		mLoop2 = 0;
//		mLoop3 = 0;
//		mLoop4 = 0;
//	}
//	mLoopc = mLoop;
//
//	int offset1 = offset + mLoop1*OHxOW;
//	int offset2 = offset1 + mLoop2*OHxOW;
//	int offset3 = offset2 + mLoop3*OHxOW;
//
//	int OutputOffset1,OutputOffset2;
//	int OutputOffset1_sum,OutputOffset1_sum1,OutputOffset1_sum2,OutputOffset1_sum3;
//	int OutputOffset2_sum;
//
//	// when TC_MIN==26,burstlength = 13*2/2=13,else 13*13*2/2=169
//	if(TC_MINe26)
//	{
//		OutputLength = 26/2;
//		OutputOffset1 = OHxOW;
//		OutputOffset2 = Output_w;
//		rLoop = 26;
//	}else//TMxTRxTC TMx13x13 continues 
//	{
//		OutputLength = 169;
//		rLoop = 1;
//		mLoop = mLoop/2;
//		OutputOffset1 = 169*2;
//		OutputOffset2 = 0;
//	}
//
//
//	bool pingpong = true;
//	int outputoffsetarray[Tn];
//	int outputoffsetarray1[Tn];
//	int tm_next[1];
//	int tm_next1[1];
//	bool wb_start_flag = true;
//	OutputOffset1_sum = offset;
//	OutputOffset1_sum1 = offset1;
//	OutputOffset1_sum2 = offset2;
//	OutputOffset1_sum3 = offset3;
//	for(tm = 0;tm < mLoop;tm++,OutputOffset1_sum += OutputOffset1,OutputOffset1_sum1 += OutputOffset1,OutputOffset1_sum2 += OutputOffset1,OutputOffset1_sum3 += OutputOffset1)
//		for(tr = 0,OutputOffset2_sum = 0;tr < rLoop + 1;tr++,OutputOffset2_sum += OutputOffset2)
//		{
//			if(pingpong)
//			{
//				outputpixel2buf( output_buffer, output_tmp00, output_tmp01,output_tmp02, output_tmp03, IsNL, InterSubOutput, LayerType, TC_MINe26, TR_MIN, TC_MIN, tm, tr,wb_start_flag,
//					  outputoffsetarray, OutputOffset1_sum, OutputOffset1_sum1,OutputOffset1_sum2, OutputOffset1_sum3, OutputOffset2_sum,tm_next,tr != rLoop);
//				mmcpy_outputpixel(Output,Output,Output,Output, output_tmp10, output_tmp11,output_tmp12, output_tmp13, tm_next1[0], mLoop1, mLoop2, mLoop3, mLoop4, outputoffsetarray1, OutputLength,tr != 0);
//				pingpong = false;
//				wb_start_flag = false;
//			}else
//			{
//				outputpixel2buf( output_buffer, output_tmp10, output_tmp11,output_tmp12, output_tmp13, IsNL, InterSubOutput, LayerType, TC_MINe26, TR_MIN, TC_MIN, tm, tr,wb_start_flag,
//					  outputoffsetarray1, OutputOffset1_sum, OutputOffset1_sum1,OutputOffset1_sum2, OutputOffset1_sum3, OutputOffset2_sum,tm_next1,tr != rLoop);
//				mmcpy_outputpixel(Output,Output,Output,Output, output_tmp00, output_tmp01, output_tmp02, output_tmp03, tm_next[0], mLoop1, mLoop2, mLoop3, mLoop4,  outputoffsetarray, OutputLength,tr != 0);
//				pingpong = true;
//				wb_start_flag = false;
//			}
//		}
//
//}
////////////////////version-0.3 end

//////////////version-0.2 start
void mmcpy_outputport(int *Output,int output_tmp[Tr*Tc/4],int tm,int mLoop,int OutputOffset,int OutputLength)
{
	bool enable = tm < mLoop;
	if(!enable)
		return;

	memcpy((int *)(Output + OutputOffset),(int *)(output_tmp),OutputLength*sizeof(int));
}

void mmcpy_outputpixel(int *Output,int *Output1,int output_tmp[Tr*Tc/4],int output_tmp1[Tr*Tc/4],int tm,int mLoop1,int mLoop2,int outputoffsetarray[2],int OutputLength,int OutputLength1,bool enable)
{
	if(!enable)
	{
		return;
	}
	mmcpy_outputport(Output ,output_tmp ,tm,mLoop1,outputoffsetarray[0],OutputLength );
	mmcpy_outputport(Output1,output_tmp1,tm,mLoop2,outputoffsetarray[1],OutputLength1);
}

void outputpixel2buf(int output_buffer[Tm][Tr][Tc],int output_tmp[Tr*Tc/4],int output_tmp1[Tr*Tc/4],bool IsNL,int InterSubOutput,int LayerType,bool TC_MINe26,int TR_MIN,int TC_MIN,int mLoop,int rLoop, bool init,
					 int outputoffsetarray[2],int OutputOffset1_sum,int OutputOffset1_sum1,int OutputOffset2_sum,int tm_next[1],bool enable)
{
	if(!enable)
	{
		return;
	}

	tm_next[0] =  mLoop;

	int tmp_output;
	int tmp_output_1;
	short tmp_output2;
	short tmp_output2_1;
	int tmp_output3;
	int tmp_output3_1;
	UCHAR cnt = 0;
	short ouput_array[2];
	short ouput_array1[2];
	int tr,tc,tm_count,tr_count;
	static int tm;

	int TM_LOOP,TR_LOOP;
	if(init)
	{
		tm = 0;
	}

	if(TC_MINe26)
	{
		tm = mLoop;
		tr = rLoop;
		TM_LOOP = 1;
		TR_LOOP = 1;
	}else
	{
		tr = 0;
		TM_LOOP = 2;
		TR_LOOP = 13;
	}

	int outputoffset = 0;
	int outputoffset1 = 0;
	for(tm_count = 0;tm_count < TM_LOOP;tm_count++,tm++,tr = 0)
		for(tr_count = 0;tr_count < TR_LOOP;tr_count++,tr++)
			for(tc = 0;tc < TC_MIN;tc++)
			{
				int tmp = output_buffer[tm][tr][tc];
				int tmp1 = output_buffer[tm + Tm/2][tr][tc];
				if(IsNL&&tmp<0)
				{
					tmp_output = ((long long)tmp*0xccc)>>15;
				}else
				{
					tmp_output = tmp;
				}

				if(IsNL&&tmp1<0)
				{
					tmp_output_1 = ((long long)tmp1*0xccc)>>15;
				}else
				{
					tmp_output_1 = tmp1;
				}

				if(LayerType==0)
				{
					tmp_output2 = tmp_output >> InterSubOutput;
					tmp_output2_1 = tmp_output_1 >> InterSubOutput;
				}
				else
				{
					tmp_output2 = tmp_output;
					tmp_output2_1 = tmp_output_1;
				}
				ouput_array[cnt] = tmp_output2;
				ouput_array1[cnt] = tmp_output2_1;
				cnt++;
				if(cnt==2)
				{
					tmp_output3 = (ouput_array[0]       &0x0000FFFF) | 
							((ouput_array[1] << 16 )&0xFFFF0000);
					tmp_output3_1 = (ouput_array1[0]       &0x0000FFFF) | 
							((ouput_array1[1] << 16 )&0xFFFF0000);

					output_tmp[outputoffset] = tmp_output3;
					outputoffset++;

					output_tmp1[outputoffset1] = tmp_output3_1;
					outputoffset1++;
					cnt = 0;
				}
			}

	outputoffsetarray[0] = (OutputOffset1_sum  + OutputOffset2_sum)>>1;
	outputoffsetarray[1] = (OutputOffset1_sum1 + OutputOffset2_sum)>>1;	

}

void write_back_output_reorg(int output_buffer[Tm][Tr][Tc],int *Output,int r,int c,int m,const int Output_w,const int Output_h,
					   const int TM_MIN,const int TR_MIN,const int TC_MIN,const int OHxOW,bool write_flag,const int OutputQ,bool IsNL,int InterSubOutput,int LayerType)
{
	static int output_tmp00[Tr*Tc/4];
	static int output_tmp01[Tr*Tc/4];

	static int output_tmp10[Tr*Tc/4];
	static int output_tmp11[Tr*Tc/4];

	int tr,tm,tc;
	int OutputLength,OutputLength1;
	int mLoopc,mLoop,mLoop1,mLoop2,rLoop;

	if(!write_flag)
		return;

	assert(TM_MIN < 128);
	assert(TR_MIN < 32);
	assert(TC_MIN < 64);

	assert(m < 1024);
	assert(r < 512);
	assert(c < 512);
	assert(OHxOW < 512*512);
	assert(Output_w < 512);

	unsigned char TM_MIN_g;
	if(TM_MIN&0x1)
	{
		TM_MIN_g = TM_MIN + 1;
		printf("TM_MIN&0x1 TM_MIN=%d\n",TM_MIN);
	}
	else
		TM_MIN_g = TM_MIN;

	const int offset = m*OHxOW + r*Output_w + c;

	bool TM_MINaboveTmdiv2 = TM_MIN_g > Tm/2;
	bool TC_MINe26 = TC_MIN == 26;
	bool TC_MINe52 = TC_MIN == 52;

	if(TM_MINaboveTmdiv2)
	{
		mLoop = Tm/2;
		mLoop1 = Tm/2;
		mLoop2 = TM_MIN_g - Tm/2;
	}else
	{
		mLoop = TM_MIN_g;
		mLoop1 = TM_MIN_g;
		mLoop2 = 0;
	}
	mLoopc = mLoop;

	int offset1 = offset + mLoop1*OHxOW;

	int OutputOffset1,OutputOffset2;
	int OutputOffset1_sum,OutputOffset1_sum1;
	int OutputOffset2_sum;

	// when TC_MIN==26,burstlength = 13*2/2=13,else 13*13*2/2=169
	if(TC_MINe26||TC_MINe52)
	{
		OutputLength = TC_MIN/2;
		OutputLength1 = TC_MIN/2;
		OutputOffset1 = OHxOW;
		OutputOffset2 = Output_w;
		rLoop = TR_MIN;
	}else//TMxTRxTC TMx13x13 continues 
	{
		OutputLength = 169;
		OutputLength1 = 169;
		rLoop = 1;
		mLoop = mLoop/2;
		OutputOffset1 = 169*2;
		OutputOffset2 = 0;
	}

	bool pingpong = true;
	int outputoffsetarray[2];
	int outputoffsetarray1[2];
	int tm_next[1];
	int tm_next1[1];
	bool wb_start_flag = true;
	for(tm = 0,OutputOffset1_sum = offset,OutputOffset1_sum1 = offset1;tm < mLoop;tm++,OutputOffset1_sum += OutputOffset1,OutputOffset1_sum1 += OutputOffset1)
		for(tr = 0,OutputOffset2_sum = 0;tr < rLoop + 1;tr++,OutputOffset2_sum += OutputOffset2,wb_start_flag = false)
		{
			if(pingpong)
			{
				outputpixel2buf( output_buffer, output_tmp00, output_tmp01, IsNL, InterSubOutput, LayerType, TC_MINe26||TC_MINe52, TR_MIN, TC_MIN, tm, tr,wb_start_flag,
					  outputoffsetarray, OutputOffset1_sum, OutputOffset1_sum1, OutputOffset2_sum,tm_next,tr != rLoop);
				mmcpy_outputpixel(Output,Output, output_tmp10, output_tmp11, tm_next1[0], mLoop1, mLoop2, outputoffsetarray1, OutputLength, OutputLength1,tr != 0);
				pingpong = false;
			}else
			{
				outputpixel2buf( output_buffer, output_tmp10, output_tmp11, IsNL, InterSubOutput, LayerType, TC_MINe26||TC_MINe52, TR_MIN, TC_MIN, tm, tr,wb_start_flag,
					  outputoffsetarray1, OutputOffset1_sum, OutputOffset1_sum1, OutputOffset2_sum,tm_next1,tr != rLoop);
				mmcpy_outputpixel(Output,Output, output_tmp00, output_tmp01, tm_next[0], mLoop1, mLoop2, outputoffsetarray, OutputLength, OutputLength1,tr != 0);
				pingpong = true;
			}
		}

}
//////////////////version-0.2 end

void pool_yolo2(short Input[Tn][OnChipIB_Height][OnChipIB_Width],int Output[Tm][Tr][Tc],
		  const int Kernel_size,const int Kernel_stride,
		  const int TM_MIN,const int TR_MIN,const int TC_MIN,bool enable)
{

	if(!enable)
		return;

	assert(TR_MIN < 32);
	assert(TC_MIN < 64);
	assert(Kernel_stride < 4);

	int i,j,tr,tc,of;
	short tmp[Tn];
	short input_short[Tn];

	for(tr = 0;tr < TR_MIN;tr++)
		for(tc = 0;tc < TC_MIN;tc++)
			for(i =0;i < 2; i++)
				for(j = 0;j < 2; j++)
				{
					for( of = 0; of < Tn; of++)
					{
						if(i==0&&j==0)
							tmp[of] = 0x8001;
						input_short[of] = Input[of][tr*Kernel_stride+i][tc*Kernel_stride+j];
						if(input_short[of] > tmp[of])
							tmp[of] = input_short[of];

						if(i==1&&j==1)
							Output[of][tr][tc] = tmp[of];
					}
				}
}

void reorg_yolo2(short Input[Tn][OnChipIB_Height][OnChipIB_Width],int Output[Tm][Tr][Tc],
		  const int Kernel_size,const int Kernel_stride,
		  const int TM_MIN,const int TR_MIN,const int TC_MIN,bool enable)
{
	int x, y,kx,ky;
	unsigned char Yoffset;
	unsigned char Xoffset;

	if(!enable)
		return;

	assert(TR_MIN < 32);
	assert(TC_MIN < 32);

    for( y = 0; y < TR_MIN; y++)
    	for( x = 0; x < TC_MIN; x++)
			for(ky= 0;ky < 2; ky++)
    			for(kx = 0;kx < 2; kx++)
				{
#pragma HLS PIPELINE
						Yoffset = (y << 1) + ky;
						Xoffset = (x << 1) + kx;

						int in_index  = (ky << 1) + kx;
						assert(in_index < 4);
						Output[in_index][y][x] = Input[0][Yoffset][Xoffset];					
    			}
}

void select_layer(short input_buffer[Tn][OnChipIB_Height][OnChipIB_Width],int output_buffer[Tm][Tr][Tc],
		short weight_buffer[Tm][Tn][K][K],short beta_buffer[MAX_BETA_LENGTH],int TMP_N_next,
		const int Kernel_size,const int Kernel_stride,int TMP_M,
		const int TM_MIN,const int TR_MIN,const int TC_MIN,bool enable,bool copy_beta_enable,bool IsNL,bool reluenable,
		UCHAR InterSubBeta,UCHAR WeightAddInputSubInter,UCHAR InterSubOutput,int LayerType)
{
	if(LayerType==0)
	{
		compute(input_buffer,output_buffer,weight_buffer,beta_buffer,TMP_N_next,Kernel_size,Kernel_stride,TMP_M,TM_MIN,TR_MIN,TC_MIN,enable,copy_beta_enable,IsNL,reluenable,
				InterSubBeta,WeightAddInputSubInter,InterSubOutput);
	}else if(LayerType==1)
	{
		pool_yolo2(input_buffer,output_buffer,Kernel_size,Kernel_stride,TM_MIN,TR_MIN,TC_MIN,enable);
	}else if(LayerType==2)
	{
		reorg_yolo2(input_buffer,output_buffer,Kernel_size,Kernel_stride,TM_MIN,TR_MIN,TC_MIN,enable);
	}

}

void intra_pingpong_wrapper(int *Input,int *Input1,int *Input2,int *Input3,int *Weight, int output_buffer[Tm][Tr][Tc],short beta_buffer[MAX_BETA_LENGTH],
								 short input_buffer0[Tn][OnChipIB_Height][OnChipIB_Width],short input_buffer1[Tn][OnChipIB_Height][OnChipIB_Width],
								 int InFM_num,int Input_w,int Input_h,int OutFM_num,int Kernel_size,int Kernel_stride,
								 int TMP_R,int TMP_C,int TMP_M,int m,int TM_MIN,int TR_MIN,int TC_MIN,int TN,UCHAR TRow,UCHAR TCol,int Padding,
								 int IHxIW,int KxK,int IFM_numxKxK,int nLoops,bool IsNL,int LayerType,int TM,int TMP_X_next[1],int TX_MIN_next[1],bool pingpongx,bool input_flag,bool process_flag,
								 UCHAR InterSubBeta,UCHAR WeightAddInputSubInter,UCHAR InterSubOutput,int nLoops_bound,bool nLoopsEq1)
{

	static short weight_buffer0[Tm][Tn][K][K];
#pragma HLS ARRAY_PARTITION variable=weight_buffer0 complete dim=1
#pragma HLS ARRAY_PARTITION variable=weight_buffer0 complete dim=2

	static short weight_buffer1[Tm][Tn][K][K];
#pragma HLS ARRAY_PARTITION variable=weight_buffer1 complete dim=1
#pragma HLS ARRAY_PARTITION variable=weight_buffer1 complete dim=2

	static int TMP_N_next0[1] = {0};
	static int TMP_N_next1[1] = {0};
	static int tmp_x;
	static int tmp_tx_min;

	bool pingpong;
	int TMP_M_conv,TM_MIN_conv;
	int TMP_N_all;


	if(nLoopsEq1)
	{
		TMP_M_conv = tmp_x;
		TM_MIN_conv = tmp_tx_min;
		TMP_X_next[0] = tmp_x;
		TX_MIN_next[0] = tmp_tx_min;
		tmp_x = TMP_M;
		tmp_tx_min = TM_MIN;
		pingpong = pingpongx;
	}else//conv nLoops > 1
	{
		if(!input_flag)
			return;

		TMP_X_next[0] = TMP_M;
		TX_MIN_next[0] = TM_MIN;
		TMP_M_conv = TMP_M;
		TM_MIN_conv = TM_MIN;
		pingpong = 0;
	}

	bool weight_load_flag;
	if(LayerType==0)
	{
		weight_load_flag = 1;
	}else
	{
		weight_load_flag = 0;
	}

	int n;
	int TMP_N;
	bool input_weight_enable_flag;
	bool compute_enable,load_local_beta_enable,relu_enable;

	for(TMP_N = 0,n = 0;n < nLoops_bound; n++,TMP_N += TN)
	{
		if(nLoopsEq1)
		{
			input_weight_enable_flag = input_flag;
			compute_enable = process_flag;
			load_local_beta_enable = process_flag;
			relu_enable = process_flag;
		}else
		{
			input_weight_enable_flag = (n!=nLoops);
			compute_enable = (n!=0);
			load_local_beta_enable = (n==1);
			relu_enable = (n==nLoops);
		}

		if(LayerType==0)
		{
			TMP_N_all = TMP_N;
		}else
		{
			TMP_N_all = TMP_M;
		}

		if(pingpong == 1)
		{
			copy_input_weight(Input,Input1,Input2,Input3,Weight,InFM_num,Input_w,Input_h,OutFM_num,Kernel_size,Kernel_stride,TMP_R,TMP_C,TMP_M,TMP_N_all,
				TM_MIN,TN,TRow,TCol,Padding,input_buffer1,weight_buffer1,TMP_N_next1,input_weight_enable_flag,weight_load_flag,IHxIW,KxK,IFM_numxKxK,LayerType);
			select_layer(input_buffer0,output_buffer,weight_buffer0,beta_buffer,TMP_N_next0[0],Kernel_size,Kernel_stride,TMP_M_conv,TM_MIN_conv,TR_MIN,TC_MIN,compute_enable,load_local_beta_enable,IsNL,relu_enable,
					InterSubBeta,WeightAddInputSubInter,InterSubOutput,LayerType);
			pingpong = 0;
		}else
		{
			copy_input_weight(Input,Input1,Input2,Input3,Weight,InFM_num,Input_w,Input_h,OutFM_num,Kernel_size,Kernel_stride,TMP_R,TMP_C,TMP_M,TMP_N_all,
				TM_MIN,TN,TRow,TCol,Padding,input_buffer0,weight_buffer0,TMP_N_next0,input_weight_enable_flag,weight_load_flag,IHxIW,KxK,IFM_numxKxK,LayerType);
			select_layer(input_buffer1,output_buffer,weight_buffer1,beta_buffer,TMP_N_next1[0],Kernel_size,Kernel_stride,TMP_M_conv,TM_MIN_conv,TR_MIN,TC_MIN,compute_enable,load_local_beta_enable,IsNL,relu_enable,
					InterSubBeta,WeightAddInputSubInter,InterSubOutput,LayerType);
			pingpong = 1;
		}

	}
}

void copy_beta(short beta_buffer[MAX_BETA_LENGTH],int *Beta,const int OFM_NUM,const int BetaQ)
{
	static int beta_tmp[MAX_BETA_LENGTH/2];
	int NUM = (OFM_NUM+1)>>1;
	memcpy(beta_tmp,(int *)Beta,NUM*sizeof(int));
	int x;
	for(x = 0;x < NUM;x++)
	{
		beta_buffer[2*x] = beta_tmp[x];
		beta_buffer[2*x+1] = beta_tmp[x]>>16;
	}
}

void YOLO2_FPGA(int *Input,int *Input1,int *Input2,int *Input3,int *Output,int *Weight,int *Beta,const int InFM_num,const int OutFM_num,
							  const int Kernel_size,const int Kernel_stride,
							  const int Input_w,const int Input_h,const int output_w,const int output_h,const int Padding,const bool IsNL,const bool IsBN,
							  const int TM,const int TN,const int TR,const int TC,
							  const int mLoops,const int nLoops,const int rLoops,const int cLoops,const int LayerType,
							  const int InputQ,const int OutputQ,const int WeightQ,const int BetaQ,bool IsPool)
{
	assert(Kernel_size < 4);
	assert(Kernel_stride < 4);
	assert(TR < 32);
	assert(TC < 64);
	assert(InFM_num < 2048);
	assert(OutFM_num < 2048);
	assert(output_h < 512);
	assert(output_w < 512);
	assert(Input_h < 1024);//gg
	assert(Input_w < 512);

	const int OHxOW = output_h*output_w;
	const UCHAR TRow = (TR-1)*Kernel_stride+Kernel_size;
	const UCHAR TCol = (TC-1)*Kernel_stride+Kernel_size;
	const int IHxIW   = Input_h*Input_w;
	const int KxK = Kernel_size*Kernel_size;
	assert(KxK < 10);
	const int IFM_numxKxK = InFM_num*KxK;
	const bool nLoopsEq1 = (nLoops==1);
	const int mLoops_bound = nLoopsEq1 ? (mLoops + 2): (mLoops + 1);
	const int nLoops_bound = nLoopsEq1 ?  1 : (nLoops+1);
	const UCHAR InterSubBeta = INTERWIDTH - BetaQ;
	const UCHAR WeightAddInputSubInter = WeightQ + InputQ - INTERWIDTH;
	const UCHAR InterSubOutput = INTERWIDTH - OutputQ;

	assert(InterSubBeta < 16);
	assert(WeightAddInputSubInter < 16);
	assert(InterSubOutput < 16);

	assert(TRow < 64);
	assert(TCol < 256);

	static short input_buffer0[Tn][OnChipIB_Height][OnChipIB_Width];
#pragma HLS ARRAY_PARTITION variable=input_buffer0 complete dim=1

	static short input_buffer1[Tn][OnChipIB_Height][OnChipIB_Width];
#pragma HLS ARRAY_PARTITION variable=input_buffer1 complete dim=1

	static int output_buffer[Tm][Tr][Tc];
#pragma HLS ARRAY_PARTITION variable=output_buffer complete dim=1

	static int output_buffer1[Tm][Tr][Tc];
#pragma HLS ARRAY_PARTITION variable=output_buffer1 complete dim=1

	static short beta_buffer[MAX_BETA_LENGTH];

	int r,c,m;
/////////////////////////////////param
	int TMP_R,TMP_C,TMP_M;
	int TM_MIN,TR_MIN,TC_MIN;
///////////////////////////////////////

	int TMP_M_next0[1];
	int TMP_M_next1[1];
	int TM_MIN_next0[1];
	int TM_MIN_next1[1];
	bool pingpongm;

	if(LayerType==0)
		//memcpy(beta_buffer,Beta,OutFM_num*sizeof(float));
		copy_beta(beta_buffer,Beta,OutFM_num,BetaQ);

	for(TMP_R = 0,r = 0; r < rLoops; r++, TMP_R += TR)
	{
		TR_MIN = MIN(TR,output_h -TMP_R);
		for(TMP_C = 0,c = 0; c < cLoops; c++,TMP_C += TC)
		{
			TC_MIN = MIN(TC,output_w -TMP_C);
			pingpongm = 0;
			for(TMP_M = 0, m = 0; m < mLoops_bound; m++,TMP_M += TM)
			{
				TM_MIN = MIN(TM,OutFM_num-TMP_M);
				bool MneZero = (m!=0);
				bool MneOne = (m!=1);
				bool MnemLoops = (m!=mLoops);
				bool MneMLoopsaddOne = (m!=(mLoops+1));
				bool input_flag = nLoopsEq1 ? MnemLoops&&MneMLoopsaddOne: MnemLoops;
				bool process_flag = nLoopsEq1 ? MneZero&&MneMLoopsaddOne : MnemLoops;
				bool write_flag = nLoopsEq1 ? MneZero&&MneOne : MneZero;

				if(pingpongm==0)
				{
					intra_pingpong_wrapper(Input,Input1,Input2,Input3,Weight,output_buffer1,beta_buffer,input_buffer0,input_buffer1,
									InFM_num, Input_w, Input_h, OutFM_num, Kernel_size, Kernel_stride,
									TMP_R, TMP_C, TMP_M, m, TM_MIN, TR_MIN, TC_MIN, TN, TRow, TCol, Padding,IHxIW,KxK,IFM_numxKxK,nLoops,IsNL,LayerType,TM, TMP_M_next1,TM_MIN_next1, pingpongm, input_flag,
									process_flag,InterSubBeta,WeightAddInputSubInter,InterSubOutput,nLoops_bound,nLoopsEq1);

					write_back_output_reorg(output_buffer,Output,TMP_R,TMP_C,TMP_M_next0[0],output_w,output_h,TM_MIN_next0[0],TR_MIN,TC_MIN,OHxOW,write_flag,OutputQ,IsNL,InterSubOutput,LayerType);
					pingpongm = 1;
				}else
				{
					intra_pingpong_wrapper(Input,Input1,Input2,Input3,Weight,output_buffer,beta_buffer,input_buffer0,input_buffer1,
									InFM_num, Input_w, Input_h, OutFM_num, Kernel_size, Kernel_stride,
									TMP_R, TMP_C, TMP_M, m, TM_MIN, TR_MIN, TC_MIN, TN, TRow, TCol, Padding,IHxIW,KxK,IFM_numxKxK,nLoops,IsNL,LayerType,TM, TMP_M_next0,TM_MIN_next0, pingpongm, input_flag,
									process_flag,InterSubBeta,WeightAddInputSubInter,InterSubOutput,nLoops_bound,nLoopsEq1);

					write_back_output_reorg(output_buffer1,Output,TMP_R,TMP_C,TMP_M_next1[0],output_w,output_h,TM_MIN_next1[0],TR_MIN,TC_MIN,OHxOW,write_flag,OutputQ,IsNL,InterSubOutput,LayerType);
					pingpongm = 0;
				}

			}
		}
	}
}

float mm(int Length,int MAX_BurstLenth)//100MHz MAX_burstlength 1-256;Length 32bit
{
	static float burst_speed[256] = {
	15.05800533,29.34379959,42.38548279,55.42713928,66.22721863,77.78242493,87.62513733,98.15619659,107.29577637,116.79578400,125.73155212,134.63140869,
	141.88391113,148.38928223,156.07928467,163.48634338,170.14941406,177.13075256,181.25485229,187.66236877,193.85479736,199.86259460,203.14558411,209.22280884,
	213.59533691,218.88497925,221.76406860,228.32760620,230.62730408,235.31747437,239.19511414,243.42375183,248.04182434,252.41569519,256.00204468,260.51312256,
	262.14251709,268.57128906,271.75299072,275.59240723,278.83673096,282.65679932,285.17068481,288.78131104,291.79641724,295.63247681,298.81549072,301.10278320,
	304.47772217,307.27130127,309.20263672,312.71987915,314.80880737,318.11676025,320.49996948,323.66714478,326.11132812,328.03018188,330.33621216,332.81158447,
	335.37176514,337.15087891,339.76406860,339.08181763,344.37857056,346.02075195,348.17236328,350.02899170,352.33752441,353.58529663,355.75714111,357.36819458,
	359.96310425,361.75564575,363.07525635,365.12591553,366.73275757,367.72943115,369.98068237,371.05322266,373.37594604,374.69409180,376.81637573,378.29977417,
	379.45263672,380.83676147,382.36120605,384.13751221,385.14309692,386.82614136,386.37542725,389.87066650,390.82537842,392.14004517,393.50469971,394.79852295,
	395.65277100,397.14306641,398.12384033,400.01998901,401.01757812,401.88888550,403.36050415,404.34927368,404.94284058,406.53247070,407.24127197,408.88299561,
	409.66293335,411.19213867,412.14807129,412.79403687,413.89123535,414.95388794,416.26556396,416.86749268,417.96737671,417.39764404,420.16253662,420.72879028,
	421.67681885,422.52032471,423.63345337,424.11349487,425.22940063,425.69323730,427.26483154,428.31137085,428.70156860,429.70611572,430.31573486,430.62844849,
	431.84301758,432.36230469,433.64840698,434.03955078,435.16101074,435.91384888,436.47274780,437.22418213,437.87030029,439.00265503,439.38238525,440.08636475,
	439.53326416,441.79367065,442.21493530,442.83609009,443.55117798,444.35803223,444.68222046,445.45291138,445.71969604,447.06472778,447.58062744,447.90951538,
	448.83303833,449.37823486,449.52343750,450.28564453,450.82168579,451.87210083,452.07318115,452.95303345,453.47616577,453.97476196,454.44863892,454.81356812,
	455.87615967,456.19461060,456.67639160,456.08407593,458.02291870,458.26889038,458.78137207,459.50274658,459.96176147,460.23300171,460.84609985,460.99877930,
	462.05383301,462.45446777,462.68850708,463.36853027,463.81854248,463.96310425,464.64352417,464.98785400,465.86788940,465.97305298,466.61175537,467.02032471,
	467.45355225,467.70974731,468.26071167,468.94006348,469.22540283,469.52145386,469.04315186,470.62976074,470.83404541,471.17373657,471.84417725,472.15051270,
	472.36654663,472.87960815,472.98446655,473.80032349,474.16189575,474.35165405,474.84439087,475.15460205,475.35223389,475.91427612,476.19403076,476.90371704,
	476.92501831,477.48367310,477.90081787,478.21862793,478.43313599,478.92361450,479.32894897,479.50131226,479.71697998,479.32174683,480.73312378,480.87759399,
	481.11618042,481.64843750,481.96038818,482.14916992,482.54544067,482.58181763,483.29241943,483.58822632,483.76000977,484.05273438,484.33847046,484.51446533,
	485.07998657,485.27493286,485.82012939,485.89019775,486.26675415,486.70312500,486.99197388,487.09207153,487.57818604,487.81231689,488.12112427,488.15835571,
	487.70080566,488.99755859,489.16574097,489.77218628
	};


	float latency = 0.0;
	int Loops = Length/MAX_BurstLenth;
	latency = Loops*MAX_BurstLenth*4.0/1024/1024/burst_speed[MAX_BurstLenth-1];
	int others = Length%MAX_BurstLenth;
	latency += others*4.0/1024/1024/burst_speed[others-1];
	return latency;
}

void yolov2_hls_ps(network *net, float *input)
{
	int x;

	network orig = *net;
	net->input = input;

	int weight_offset[32] = {864, 18432, 73728, 8192, 73728,
		294912, 32768, 294912, 1179648, 131072, 1179648, 131072,
		1179648, 4718592, 524288, 4718592, 524288, 4718592, 9437184,
		9437184, 32768, 11796480, 435200, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int beta_offset[32] = {32, 64, 128, 64, 128, 256, 128, 256, 512, 256, 512, 256, 512, 1024,
		512, 1024, 512, 1024, 1024, 1024, 64, 1024, 425, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int offset_index = 0;

	int *Weight_buf = (int *)calloc(203767168/4/2,sizeof(int));
	int *Beta_buf   = (int *)calloc((43044+4)/4/2,sizeof(int));

	FILE *fp_w = fopen("weightsv2_comb_reorg_ap16.bin", "rb");
    if(!fp_w) file_error("weightsv2_comb_reorg_ap16.bin");

	FILE *fp_b = fopen("biasv2_comb_ap16.bin", "rb");
    if(!fp_b) file_error("biasv2_comb_ap16.bin");

	fread(Weight_buf, sizeof(int), 203767168/4/2, fp_w);
	fread(Beta_buf, sizeof(int), (43044+4)/4/2, fp_b);

	fclose(fp_w);
	fclose(fp_b);

#define QNUM 23

	int inputQ[QNUM+1];
	int weightQ[QNUM];
	int betaQ[QNUM];
	FILE *Qin;

	Qin = fopen("yolov2_ap16_inout_maxQ_24.bin","rb");
	if(!Qin) file_error("Qin error 1\n");
	fread(inputQ,sizeof(int),QNUM+1,Qin);
	fclose(Qin);

	if(inputQ[20] < inputQ[21])
		inputQ[21] = inputQ[20];
	else
		inputQ[20] = inputQ[21];


	for(x=0;x<QNUM+1;x++)
		printf("[%2d inputQ]=%2d\n",x,inputQ[x]);

	Qin = fopen("weightsv2_comb_reorg_ap16_maxQ_23.bin","rb");
	if(!Qin) file_error("Qin error 2\n");
	fread(weightQ,sizeof(int),QNUM,Qin);
	fclose(Qin);
	
	for(x=0;x<QNUM;x++)
		printf("[%2d weightQ]=%2d\n",x,weightQ[x]);

	Qin = fopen("biasv2_comb_ap16_maxQ_23.bin","rb");
	if(!Qin) file_error("Qin error 4\n");
	fread(betaQ,sizeof(int),QNUM,Qin);
	fclose(Qin);

	for(x=0;x<QNUM;x++)
		printf("[%2d betaQ]=%2d\n",x,betaQ[x]);


#define MEM_LEN (416*416*32/2+208*208*32/2)
	int *Memory_buf = (int*)calloc(MEM_LEN+1024/2+1024/2,sizeof(int));
	int *Memory_top = Memory_buf+1024/2;
	int *Memory_bottom = Memory_top + MEM_LEN;

	int tmp_in;
	short current_in,next_in;
	bool NextPixelInFlag = true;
	int InputPixelOffset = 0;
	int *Input_ptr = (int *)Memory_top;
	for(x=0;x<416*416*3;x++)//1st Layer input Q14
	{
		if(NextPixelInFlag)
		{
			current_in = (short)(input[x]*pow(2.0,14));
			NextPixelInFlag = false;
		}
		else
		{
			next_in = (short)(input[x]*pow(2.0,14));
			tmp_in = (next_in<<16) + (current_in);
			Input_ptr[InputPixelOffset] = tmp_in;
			InputPixelOffset++;
			NextPixelInFlag = true;
		}
	}

	float *region_buf = (float *)calloc(sizeof(float),13*13*425); 

	int* in_ptr[32];
	int* out_ptr[32];

#define ROUTE16_LEN (26*26*512/2)
#define CONV27_LEN (13*13*256/2)
#define CONV24_LEN (13*13*1024/2)

	for(x=0;x<18;x++)
	{
		if(x%2==0)
		{
			in_ptr[x] = Memory_top;
			out_ptr[x] = Memory_bottom - net->layers[x].outputs/2 ;
		}
		else
		{
			in_ptr[x] = out_ptr[x-1];
			out_ptr[x] = Memory_top;
		}
	}

	for(x=18;x<25;x++)
	{
		if(x%2==0)
		{
			in_ptr[x] = Memory_top;
			out_ptr[x] = Memory_bottom - ROUTE16_LEN - net->layers[x].outputs/2;
		}else
		{
			in_ptr[x] = out_ptr[x-1];
			out_ptr[x] = Memory_top;
		}
	}

	in_ptr[26] = Memory_bottom - ROUTE16_LEN;
	out_ptr[26] = Memory_top;

	in_ptr[27] = Memory_top;
	out_ptr[27] = Memory_bottom - ROUTE16_LEN - CONV24_LEN - CONV27_LEN;

	in_ptr[29] = out_ptr[27];
	out_ptr[29] = Memory_top;

	in_ptr[30] = Memory_top;
	out_ptr[30] = Memory_bottom - (net->layers[30].outputs + 13*13*3)/2;

	in_ptr[31] = out_ptr[30];

    network netp = *net;
    int i;
	int woffset = 0;
	int aoffset = 0;
	int boffset = 0;
	int TR,TC,TM,TN;
	int output_w,output_h;
	int rLoops,cLoops,mLoops,nLoops;
	double sum_gop = 0.0;
	int INPUTQ;
	bool IsPool;

//////////////eval start
	int T2Rate,ColIncreaseLength;
	int trow_loops;
	int omLoops,orLoops;
	const int Cin = 4;
	const int Cout = 2;
	const float freq = 150000000;
	const int rw_fm_max_burstlength = 64;
	const int r_wb_max_burstlength = 128;
	float load_ifm,load_w,compute,store_ofm;
	float load_w1,load_w2;
	float store_o1,store_o2;
	float load_ifm1,load_ifm2;
	float layper_latency;
	float inner_loop_latency;
	float load_ifm_latency,load_w_latency,compute_latency,store_ofm_latency;
	float load_ifm_latency_array[32];
	float load_w_latency_array[32];
	float compute_latency_array[32];
	float store_ofm_latency_array[32];
	float layper_latency_array[32];
	int latency_cnt = 0;
	int TRow;
	int TCol;
//////////////eval end

    for(i = 0; i < netp.n; ++i)
	{
        netp.index = i;
        layer l = netp.layers[i];
		printf("Layer[%2d]: ",i);
		switch(l.type)
		{
			case CONVOLUTIONAL:
				printf("outputMemory:%8d;BN=%d;Activation=%d;conv  %5d %2d x%2d /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d  %5.3f BFLOPs\n",l.outputs,l.batch_normalize,l.activation, l.n, l.size, l.size, l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c, (2.0 * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w)/1000000000.);
				sum_gop += (2.0 * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w)/1000000000.;
				output_w = (l.w - l.size + 2*l.pad)/l.stride + 1 ;
				output_h = (l.h - l.size + 2*l.pad)/l.stride + 1 ;

				TR = MIN(((OnChipIB_Height-l.size)/l.stride+1),Tr);//keep Kernel_stride>=1
				TR = MIN(output_h,TR);
				TC = MIN(((OnChipIB_Width-l.size)/l.stride+1),Tc);
				TC = MIN(output_w,TC);
				TM = MIN(l.n,Tm);
				TN = MIN(l.c,Tn);

				rLoops = (int)ceil(((float)output_h)/TR);
				cLoops = (int)ceil(((float)output_w)/TC);
				mLoops = (int)ceil(((float)l.n)/TM);
			    nLoops = (int)ceil(((float)l.c)/TN);

				INPUTQ = inputQ[offset_index];
				if(i==26)
					INPUTQ = inputQ[12];
				if(i==0||i==2||i==6||i==10)
					IsPool = true;
				else
					IsPool = false;

				YOLO2_FPGA(in_ptr[i],in_ptr[i],in_ptr[i],in_ptr[i],out_ptr[i],Weight_buf+woffset/2,Beta_buf+boffset/2,
					l.c,l.n,l.size,
					l.stride,l.w,l.h,output_w,output_h,
					l.pad,l.activation==LEAKY?1:0,l.batch_normalize?1:0,
					TM,TN,TR,TC,
					mLoops,nLoops,rLoops,cLoops,0,
					INPUTQ,inputQ[offset_index+1],weightQ[offset_index],betaQ[offset_index],IsPool);
				
				TRow = (TR-1)*l.stride+l.size;
				TCol = (TC-1)*l.stride+l.size;
				switch(l.w)
				{
					case 26:
						T2Rate = 2;
						break;
					case 13:
						T2Rate = 4;
						break;
					default:
						T2Rate = 1;
						break;
				}

				load_ifm1 = 5/freq + mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
				load_ifm2 = 5/freq + T2Rate*TCol/freq;
				trow_loops = (int)ceil(((float)TRow/T2Rate));
				load_ifm = 15/freq + load_ifm1 + load_ifm2 + (trow_loops-1)*MAX(load_ifm1,load_ifm2);

				load_w1 = (Tm*Tn+10)/freq;
				load_w2 = 5/freq + mm(TM*TN/2,r_wb_max_burstlength);
				load_w = l.size*(load_w1 + load_w2 + (l.size-1)*MAX(load_w1,load_w2));

				compute = (10 + l.size*l.size*TR*TC)/freq;

				store_o1 = mm((TC == 26)?13:169,rw_fm_max_burstlength);
				store_o2 = (5 + ((TC == 26)?26:2*13*13))/freq;

				if(TM > Tm/2)
				{
					omLoops = Tm/2;
				}else
				{
					omLoops = TM;
				}

				if(TC == 26)
				{
					orLoops = 26;
				}else//TMxTRxTC TMx13x13 continues
				{
					orLoops = 1;
					omLoops = omLoops/2;
				}

				store_ofm = (30)/freq + omLoops*(store_o1 + store_o2 + (orLoops-1)*MAX(store_o1,store_o2));

				load_ifm_latency = rLoops*cLoops*mLoops*nLoops*load_ifm;
				load_w_latency = rLoops*cLoops*mLoops*nLoops*load_w;
				store_ofm_latency = rLoops*cLoops*mLoops*store_ofm;
				compute_latency = rLoops*cLoops*mLoops*(nLoops*compute+TM/freq);
				inner_loop_latency = ((nLoops-1)*MAX(MAX(load_ifm,load_w),compute)+MAX(load_ifm,load_w)+compute);
				layper_latency = rLoops*cLoops*((mLoops-1)*MAX(inner_loop_latency,store_ofm)+inner_loop_latency+store_ofm);

				load_ifm_latency_array[latency_cnt] = load_ifm_latency;
				load_w_latency_array[latency_cnt] = load_w_latency;
				compute_latency_array[latency_cnt] = compute_latency;
				store_ofm_latency_array[latency_cnt] = store_ofm_latency;
				layper_latency_array[latency_cnt] = layper_latency;
				latency_cnt++;


				printf("TR=%d,TC=%d,TM=%d,TN=%d,rLoops=%d,cLoops=%d,mLoops=%d,nLoops=%d,IsPool=%d\n",TR,TC,TM,TN,rLoops,cLoops,mLoops,nLoops,IsPool);

				woffset += weight_offset[offset_index];
				boffset += beta_offset[offset_index];
				offset_index++;

				break;
			case MAXPOOL:
				printf("outputMemory:%8d;max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n",l.outputs, l.size, l.size, l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c);
				output_w = (l.w - l.size)/l.stride + 1 ;
				output_h = (l.h - l.size)/l.stride + 1 ;
				//output_w = l.out_h;
				//output_h = l.out_w;

				TR = MIN(((OnChipIB_Height-l.size)/l.stride+1),Tr);//keep Kernel_stride>=1
				TC = MIN(((OnChipIB_Width-l.size)/l.stride+1),Tc);

				TR = MIN(output_h,TR);
				TC = MIN(output_w,TC);
				TM = MIN(Tm,Tn);
				TM = MIN(l.c,TM);
				TN = TM;

				rLoops = (int)ceil(((float)output_h)/TR);
				cLoops = (int)ceil(((float)output_w)/TC);
				mLoops = (int)ceil(((float)l.c)/TM);

				YOLO2_FPGA(in_ptr[i],in_ptr[i],in_ptr[i],in_ptr[i],out_ptr[i],NULL,NULL,l.c,l.c,
					l.size,l.stride,l.w,l.h,output_w,output_h,
					0,0,0,TM,TN,TR,TC,mLoops,1,rLoops,cLoops,1,
					inputQ[offset_index],inputQ[offset_index],INTERWIDTH,INTERWIDTH,false);

				TRow = (TR-1)*l.stride+l.size;
				TCol = (TC-1)*l.stride+l.size;
				switch(l.w)
				{
					case 26:
						T2Rate = 2;
						break;
					case 13:
						T2Rate = 4;
						break;
					default:
						T2Rate = 1;
						break;
				}

				load_ifm1 = 5/freq + mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
				load_ifm2 = 5/freq + T2Rate*TCol/freq;
				trow_loops = (int)ceil(((float)TRow/T2Rate));
				load_ifm = 15/freq + load_ifm1 + load_ifm2 + (trow_loops-1)*MAX(load_ifm1,load_ifm2);

				compute = (5 + l.size*l.size*TR*TC)/freq;

				store_o1 = mm((TC == 26)?13:169,rw_fm_max_burstlength);
				store_o2 = (5 + ((TC == 26)?26:2*13*13))/freq;

				if(TM > Tm/2)
				{
					omLoops = Tm/2;
				}else
				{
					omLoops = TM;
				}

				if(TC == 26)
				{
					orLoops = 26;
				}else//TMxTRxTC TMx13x13 continues
				{
					orLoops = 1;
					omLoops = omLoops/2;
				}

				store_ofm = (30)/freq + omLoops*(store_o1 + store_o2 + (orLoops-1)*MAX(store_o1,store_o2));

				load_ifm_latency = rLoops*cLoops*mLoops*load_ifm;
				store_ofm_latency = rLoops*cLoops*mLoops*store_ofm;
				compute_latency = rLoops*cLoops*mLoops*compute;
				/*layper_latency = rLoops*cLoops*((mLoops-1)*MAX(load_ifm,store_ofm)+ load_ifm + compute + store_ofm);*/
				layper_latency = rLoops*cLoops*(mLoops*MAX(load_ifm,MAX(compute,store_ofm))+ load_ifm + store_ofm);

				load_ifm_latency_array[latency_cnt] = load_ifm_latency;
				load_w_latency_array[latency_cnt] = 0;
				compute_latency_array[latency_cnt] = compute_latency;
				store_ofm_latency_array[latency_cnt] = store_ofm_latency;
				layper_latency_array[latency_cnt] = layper_latency;
				latency_cnt++;

				break;
			case REORG:
				printf("outputMemory:%8d;reorg              /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n",l.outputs,  l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c);			
				output_w = 26;
				output_h = 32*13;

				TR = MIN(((OnChipIB_Height-l.stride)/l.stride+1),Tr);//keep Kernel_stride>=1
				TR = MIN(output_h,TR);
				TC = MIN(((OnChipIB_Width-l.stride)/l.stride+1),Tc);
				TC = MIN(output_w,TC);
				TM = 4;
				TN = TM;

				rLoops = (int)ceil(((float)output_h)/TR);
				cLoops = (int)ceil(((float)output_w)/TC);
				mLoops = 1;

				YOLO2_FPGA(in_ptr[i],in_ptr[i],in_ptr[i],in_ptr[i],out_ptr[i],NULL,NULL,1,4,
					l.stride,l.stride,52,32*26,output_w,output_h,
					0,0,0,TM,TN,TR,TC,mLoops,1,rLoops,cLoops,2,
					inputQ[offset_index],inputQ[offset_index],INTERWIDTH,INTERWIDTH,false);

				TRow = (TR-1)*l.stride+l.stride;
				TCol = (TC-1)*l.stride+l.stride;
				switch(52)
				{
					case 26:
						T2Rate = 2;
						break;
					case 13:
						T2Rate = 4;
						break;
					default:
						T2Rate = 1;
						break;
				}

				load_ifm1 = 5/freq + mm(T2Rate*TCol/2.0,rw_fm_max_burstlength);
				load_ifm2 = 5/freq + T2Rate*TCol/freq;
				trow_loops = (int)ceil(((float)TRow/T2Rate));
				load_ifm = 15/freq + load_ifm1 + load_ifm2 + (trow_loops-1)*MAX(load_ifm1,load_ifm2);

				compute = (5 + l.stride*l.stride*TR*TC)/freq;

				store_o1 = mm((TC == 26)?13:169,rw_fm_max_burstlength);
				store_o2 = (5 + ((TC == 26)?26:2*13*13))/freq;

				if(TM > Tm/2)
				{
					omLoops = Tm/2;
				}else
				{
					omLoops = TM;
				}

				if(TC == 26)
				{
					orLoops = 26;
				}else//TMxTRxTC TMx13x13 continues
				{
					orLoops = 1;
					omLoops = omLoops/2;
				}

				store_ofm = (30)/freq + omLoops*(store_o1 + store_o2 + (orLoops-1)*MAX(store_o1,store_o2));

				load_ifm_latency = rLoops*cLoops*mLoops*load_ifm;
				store_ofm_latency = rLoops*cLoops*mLoops*store_ofm;
				compute_latency = rLoops*cLoops*mLoops*compute;
				//layper_latency = rLoops*cLoops*((mLoops-1)*MAX(load_ifm,store_ofm)+ load_ifm + compute + store_ofm);
				layper_latency = rLoops*cLoops*(mLoops*MAX(load_ifm,MAX(compute,store_ofm))+ load_ifm + store_ofm);

				load_ifm_latency_array[latency_cnt] = load_ifm_latency;
				load_w_latency_array[latency_cnt] = 0;
				compute_latency_array[latency_cnt] = compute_latency;
				store_ofm_latency_array[latency_cnt] = store_ofm_latency;
				layper_latency_array[latency_cnt] = layper_latency;
				latency_cnt++;

				break;
			case ROUTE:
				printf("outputMemory:%8d;route ",l.outputs);
				int j;
				for(j = 0; j < l.n; ++j){
					printf(" %d", l.input_layers[j]);
				}
				printf("\n");
				break;
			case REGION:
				printf("outputMemory:%8d;Detection\n",l.outputs);
				//netp.input = in_ptr[i];
				double LastLayerOutputPara = pow(2.0,-inputQ[QNUM]);
				bool NextPixelFlag = true;
				int OutputPixelOffset = 0;
				short current_p,next_p,output_p;
				int *Output_ptr = (int *)(in_ptr[i]);
				for(j=0;j<l.outputs;j++)
				{
					if(NextPixelFlag)
					{
						int tmp_p = Output_ptr[OutputPixelOffset];
						OutputPixelOffset++;
						current_p = tmp_p;
						next_p = tmp_p >> 16;
						output_p = current_p;
						NextPixelFlag = false;
					}else
					{
						output_p = next_p;
						NextPixelFlag = true;
					}
					region_buf[j] = output_p*LastLayerOutputPara;
				}
				netp.input = region_buf;
				forward_region_layer(l,netp);
				break;
		}

		netp.input = l.output;

    }
	printf("SUM_GOP=%g\n",sum_gop);
	*net = orig;

	netp = *net;
    for(i = 0; i < netp.n; ++i)
	{
        netp.index = i;
        layer l = netp.layers[i];
		printf("Layer[%2d]: ",i);
		switch(l.type)
		{
			case CONVOLUTIONAL:
				printf("l.stride=%d,l.pad=%d\n",l.stride,l.pad);
				//YOLO2_FPGA(in_ptr[i],in_ptr[i],in_ptr[i],in_ptr[i],out_ptr[i],Weight_buf+woffset/2,Beta_buf+boffset/2,
				//	l.c,l.n,l.size,
				//	l.stride,l.w,l.h,output_w,output_h,
				//	l.pad,l.activation==LEAKY?1:0,l.batch_normalize?1:0,
				//	TM,TN,TR,TC,
				//	mLoops,nLoops,rLoops,cLoops,0,
				//	INPUTQ,inputQ[offset_index+1],weightQ[offset_index],betaQ[offset_index],IsPool);
				break;
			case MAXPOOL:
				printf("l.stride=%d,l.pad=%d\n",l.stride,0);
				//YOLO2_FPGA(in_ptr[i],in_ptr[i],in_ptr[i],in_ptr[i],out_ptr[i],NULL,NULL,l.c,l.c,
				//	l.size,l.stride,l.w,l.h,output_w,output_h,
				//	0,0,0,TM,TN,TR,TC,mLoops,1,rLoops,cLoops,1,
				//	inputQ[offset_index],inputQ[offset_index],INTERWIDTH,INTERWIDTH,false);
				break;
			case REORG:
				printf("l.stride=%d,l.pad=%d\n",l.stride,0);
				break;
			case ROUTE:
				printf("l.stride=%d,l.pad=%d\n",l.stride,0);
				break;
			case REGION:
				printf("l.stride=%d,l.pad=%d\n",l.stride,0);
				break;
		}

		netp.input = l.output;

    }
	*net = orig;

	printf("latency_cnt=%d\n",latency_cnt);
	for(i=0;i<latency_cnt;i++)
	{
		printf("[%d]:load=%.8lf store=%.8lf compute=%.8lf,total =%.8lf\n",
		i,MAX(load_ifm_latency_array[i],load_w_latency_array[i]),store_ofm_latency_array[i],compute_latency_array[i],layper_latency_array[i]);
	}

	printf("load_latency:\n");
	for(i=0;i<latency_cnt;i++)
	{
		printf("%.8lf\n",MAX(load_ifm_latency_array[i],load_w_latency_array[i]));
	}

	printf("compute_latency:\n");
	for(i=0;i<latency_cnt;i++)
	{
		printf("%.8lf\n",compute_latency_array[i]);
	}

	printf("store_ofm_latency:\n");
	for(i=0;i<latency_cnt;i++)
	{
		printf("%.8lf\n",store_ofm_latency_array[i]);
	}

	printf("layper_latency:\n");
	for(i=0;i<latency_cnt;i++)
	{
		printf("%.8lf\n",layper_latency_array[i]);
	}

	free(region_buf);
	free(Memory_buf);
	free(Weight_buf);
	free(Beta_buf);

}
///////////////////////////////////////////////////////////////////////20181229 reorg WeightQ BetaQ ok  InputQ ok end input opt ok input_g eval op1 //out4 gg (5)n4m32i4o2 ok


/////////////////////////////////////////////////////////////////////////20181229 anti-reorg start => KxKxTmxTn
//#define MAX(x,y) ((x)>(y)?(x):(y))
//#define MIN(x,y) ((x)<(y)?(x):(y))
//#define S 2
//#define K 3
//
//#define Tn 4
//#define Tm 48
//#define Tr 26
//#define Tc 52
//#define OnChipIB_Width  ((Tc-1)*S+K)
//#define OnChipIB_Height ((Tr-1)*S+K)
//#define MAX_BETA_LENGTH (1024)
//
////////////////////////////////////////////////////T3 start
//void input_load(float *input,float input_buffer[Tn][OnChipIB_Height][OnChipIB_Width],int r,int c,int n,int Kernel_stride,int Padding,int TRow,int TCol,int Input_w,int Input_h,int TN_MIN,int IHxIW,int LayerType)
//{
//	int t1,t2,t3,t4;
//	int xoffset;
//	int yoffset;
//
//	static float input_memcpy_buffer[Tn*OnChipIB_Height*OnChipIB_Width];
//
//	const int Coffset = c*Kernel_stride - Padding;
//	const int Roffset = r*Kernel_stride - Padding;
//	const int CurrentOffset = n*IHxIW + Roffset*Input_w + Coffset;
//
//	float pad_value = 0;
//	if(LayerType==1)
//		pad_value = -1024*1024;
//
//	int input_mmcpy_offset = 0;
//	for(t1 = 0;t1 < TN_MIN; t1++)
//		for(t2 = 0;t2 < TRow; t2++)
//		{
//			memcpy((float *)(input_memcpy_buffer + input_mmcpy_offset),(float *)(input + CurrentOffset + t1*IHxIW + t2*Input_w),TCol*sizeof(float));
//			input_mmcpy_offset += TCol;
//		}
//
//	input_mmcpy_offset = 0;
//	for(t1 = 0;t1 < Tn; t1++)
//		for(t2 = 0;t2 < TRow; t2++)
//			for(t3 = 0;t3 < TCol; t3++)
//			{
//				xoffset = Coffset + t3;
//				yoffset = Roffset + t2;
//				bool XEnable    = (xoffset >= 0)&&(xoffset < Input_w);
//				bool YEnable    = (yoffset >= 0)&&(yoffset < Input_h);
//				bool PaddingEnable = XEnable&&YEnable;
//				if(PaddingEnable&&(t1 < TN_MIN))
//					input_buffer[t1][t2][t3] = input_memcpy_buffer[input_mmcpy_offset];
//				else
//					input_buffer[t1][t2][t3] = pad_value;
//				input_mmcpy_offset++;
//			}
//}
//
//void weight_load(float *Weight,float weight_buffer[Tm][Tn][K][K],bool weight_load_enable,int m,int n,int IFM_numxKxK,int KxK,int Kernel_size,int TM_MIN,int TN_MIN)
//{
//	int t1,t2,t3,t4;
//	static float weight_memcpy_buffer[Tm*Tn*K*K];
//	
//	if(!weight_load_enable)
//		return;
//	
//	const int Woffset = m*IFM_numxKxK + n*KxK;
//		
//	int weight_memcpy_offset = 0;
//	for(t1 = 0;t1 < TM_MIN; t1++)
//		for(t2 = 0;t2 < TN_MIN; t2++)
//		{
//			memcpy((float *)(weight_memcpy_buffer + weight_memcpy_offset),(float *)(Weight + Woffset + t1*IFM_numxKxK + t2*KxK),KxK*sizeof(float));
//			weight_memcpy_offset += KxK;
//		}
//	
//	weight_memcpy_offset = 0;
//	for(t1 = 0;t1 < Tm; t1++)
//		for(t2 = 0;t2 < Tn; t2++)
//			for(t3 = 0;t3 <Kernel_size; t3++)
//				for(t4 = 0;t4 <Kernel_size; t4++)
//				{
//					bool Enable = (t1 < TM_MIN)&&(t2 < TN_MIN);
//					if(Enable)
//					{
//						weight_buffer[t1][t2][t3][t4] =  weight_memcpy_buffer[weight_memcpy_offset];
//						weight_memcpy_offset++;
//					}
//					else
//						weight_buffer[t1][t2][t3][t4] = 0;
//				}
//}
//
//void weight_load_reorg(float *Weight,float weight_buffer[Tm][Tn][K][K],bool weight_load_enable,int m,int n,int IFM_numxKxK,int KxK,int Kernel_size,int TM_MIN,int TN_MIN)
//{
//	int t1,t2,t3,t4;
//	static float weight_memcpy_buffer[Tm*Tn*K*K];
//	static int Woffset;
//
//	if(!weight_load_enable)
//		return;
//
//	if(m==0&&n==0)
//		Woffset = 0;
//
//	memcpy(weight_memcpy_buffer,(float *)(Weight + Woffset),TM_MIN*TN_MIN*KxK*sizeof(float));
//	Woffset += TM_MIN*TN_MIN*KxK;
//	
//	int weight_memcpy_offset = 0;
//	for(t1 = 0;t1 < Tm; t1++)
//		for(t2 = 0;t2 < Tn; t2++)
//			for(t3 = 0;t3 <Kernel_size; t3++)
//				for(t4 = 0;t4 <Kernel_size; t4++)
//				{
//					bool Enable = (t1 < TM_MIN)&&(t2 < TN_MIN);
//					if(Enable)
//					{
//						weight_buffer[t1][t2][t3][t4] =  weight_memcpy_buffer[weight_memcpy_offset];
//						weight_memcpy_offset++;
//					}
//					else
//						weight_buffer[t1][t2][t3][t4] = 0;
//				}	
//}
//
//
//void copy_input_weight(float *input,float *Weight,int InFM_num,int Input_w,int Input_h,int OutFM_num,int Kernel_size,int Kernel_stride,int r,int c,int m,int n,
//		int TM_MIN,int TN,int TRow,int TCol,int Padding,float input_buffer[Tn][OnChipIB_Height][OnChipIB_Width],float weight_buffer[Tm][Tn][K][K],int TMP_N_next[1],
//		bool enable,bool weight_load_enable,bool initialize,const int IHxIW,const int KxK,const int IFM_numxKxK,const int LayerType)
//{
//	if(!enable)
//		return ;
//
//	const int TN_MIN = MIN(TN,InFM_num - n);
//	TMP_N_next[0] = n;
//
//	input_load(input, input_buffer, r, c, n, Kernel_stride, Padding, TRow, TCol, Input_w, Input_h, TN_MIN, IHxIW, LayerType);
//	weight_load(Weight,weight_buffer,weight_load_enable,m,n,IFM_numxKxK,KxK,Kernel_size,TM_MIN,TN_MIN);
//	//weight_load_reorg(Weight,weight_buffer,weight_load_enable,m,n,IFM_numxKxK,KxK,Kernel_size,TM_MIN,TN_MIN);
//
//}
////////////////////////////////////////////////////T3 end
//	void copy_local_beta(float beta_buffer[MAX_BETA_LENGTH],float local_beta_buffer[MAX_BETA_LENGTH],const int TM_MIN,int m)
//{
//	//memcpy(local_beta_buffer,(float *)(beta_buffer+m),TM_MIN*sizeof(float));
//	int offset;
//	int tm;
//	for(tm = 0,offset = m;tm < TM_MIN;tm++)
//	{
//		local_beta_buffer[tm] = beta_buffer[offset];
//		offset++;
//	}
//}
//
//void nonlinear_leaky(float Input[Tm][Tr][Tc],const int TM_MIN,const int TR_MIN,const int TC_MIN,const bool IsNL)
//{
//	int tr,tc,tm;
//
//	if(!IsNL)
//		return ;
//	
//	for(tm = 0;tm < TM_MIN;tm++)
//#pragma HLS LOOP_TRIPCOUNT min=1 max=1
//		for(tr = 0;tr < TR_MIN;tr++)
//#pragma HLS LOOP_TRIPCOUNT min=1 max=14
//			for(tc = 0;tc < TC_MIN;tc++)
//			{
//#pragma HLS LOOP_TRIPCOUNT min=14 max=14
//#pragma HLS PIPELINE
//				float tmp = Input[tm][tr][tc];
//				if(tmp < 0)
//					Input[tm][tr][tc] = tmp*0.1;
//			}
//
//}
//
//void compute(float input_buffer[Tn][OnChipIB_Height][OnChipIB_Width],float output_buffer[Tm][Tr][Tc],
//		float weight_buffer[Tm][Tn][K][K],float beta_buffer[MAX_BETA_LENGTH],int TMP_N_next[1],
//		const int Kernel_size,const int Kernel_stride,int TMP_M,
//		const int TM_MIN,const int TR_MIN,const int TC_MIN,bool enable,const bool IsNL,const bool reluenable)
//{
//	static float local_beta_buffer[Tm];
//#pragma HLS ARRAY_PARTITION variable=local_beta_buffer complete dim=1
//
//	if(!enable)
//	{
//		copy_local_beta(beta_buffer,local_beta_buffer,TM_MIN,TMP_M);
//		return;
//	}
//
//	int i,j,tr,tc,tm,tn;
//	int n = TMP_N_next[0];
//	float partial_mul[Tm][Tn];
//	float partial_add[Tm];
//
//	for(i =0;i < Kernel_size; i++)
//#pragma HLS LOOP_TRIPCOUNT min=1 max=5
//		for(j = 0;j < Kernel_size; j++)
//#pragma HLS LOOP_TRIPCOUNT min=1 max=5
//			for(tr = 0;tr < TR_MIN;tr++)
//#pragma HLS LOOP_TRIPCOUNT min=14 max=14
//				for(tc = 0;tc < TC_MIN;tc++)
//				{
//#pragma HLS LOOP_TRIPCOUNT min=14 max=14
//#pragma HLS PIPELINE
//					for(tm = 0;tm < Tm;tm++)
//					{
//						if(i==0&&j==0&&n==0)
//							partial_add[tm] = local_beta_buffer[tm];
//						else
//							partial_add[tm] = output_buffer[tm][tr][tc];
//					}
//
//					for(tm = 0;tm < Tm;tm++)
//						for(tn = 0;tn <Tn;tn++)
//						{
//							partial_mul[tm][tn] = weight_buffer[tm][tn][i][j]*input_buffer[tn][Kernel_stride*tr+i][Kernel_stride*tc+j];
//						}
//
//					
//					for(tm = 0;tm < Tm;tm++)
//					{
//						float partial_sum = 0;
//						for(tn = 0;tn <Tn;tn++)
//						{
//							 partial_sum += partial_mul[tm][tn];
//						}
//						output_buffer[tm][tr][tc] = partial_add[tm] + partial_sum;
//					}
//				}
//
//	if(reluenable)
//		nonlinear_leaky(output_buffer,TM_MIN,TR_MIN,TC_MIN,IsNL);
//
//}
//
//void write_back_output_reorg(float output_buffer[Tm][Tr][Tc],float *Output,int r,int c,int m,const int Output_w,const int Output_h,
//					   const int TM_MIN,const int TR_MIN,const int TC_MIN,const int OHxOW,bool write_flag)
//{
//	if(!write_flag)
//		return;
//
//	const int offset = m*OHxOW + r*Output_w + c;
//	int tr,tm;
//
//	//for(tm = 0;tm < TM_MIN;tm++)
//	//	for(tr = 0;tr < TR_MIN;tr++)
//	//		for(tc = 0;tc < TC_MIN;tc++)
//	//		{
//	//				Output[tm*OHxOW + tr*Output_w + tc + offset] = output_buffer[tm][tr][tc];
//	//		}
//
//	for(tm = 0;tm < TM_MIN;tm++)
//		for(tr = 0;tr < TR_MIN;tr++)
//		{
//			memcpy((float *)(Output + tm*OHxOW + tr*Output_w + offset),output_buffer[tm][tr],TC_MIN*sizeof(float));
//		}
//}
//
//void pool_yolo2(float Input[Tn][OnChipIB_Height][OnChipIB_Width],float Output[Tm][Tr][Tc],
//		  const int Kernel_size,const int Kernel_stride,
//		  const int TM_MIN,const int TR_MIN,const int TC_MIN,bool enable)
//{
//	if(!enable)
//		return;
//
//	int i,j,tr,tc,of;
//	float tmp[Tn];
//
//	for(tr = 0;tr < TR_MIN;tr++)
//		for(tc = 0;tc < TC_MIN;tc++)
//			for(i =0;i < Kernel_size; i++)
//				for(j = 0;j < Kernel_size; j++)
//				{
//#pragma HLS PIPELINE
//					for( of = 0; of < Tn; of++)
//					{
//						if(i==0&&j==0)
//							tmp[of] = -1024*1024;
//
//						if(Input[of][tr*Kernel_stride+i][tc*Kernel_stride+j] > tmp[of])
//							tmp[of] = Input[of][tr*Kernel_stride+i][tc*Kernel_stride+j];
//
//						if(i==1&&j==1)
//							Output[of][tr][tc] = tmp[of];
//					}
//				}
//
//}
//
//void reorg_yolo2(float Input[Tn][OnChipIB_Height][OnChipIB_Width],float Output[Tm][Tr][Tc],
//		  const int Kernel_size,const int Kernel_stride,
//		  const int TM_MIN,const int TR_MIN,const int TC_MIN,bool enable)
//{
//	int x, y,kx,ky;
//	unsigned char Yoffset;
//	unsigned char Xoffset;
//
//	if(!enable)
//		return;
//
//    for( y = 0; y < TR_MIN; y++)
//    	for( x = 0; x < TC_MIN; x++)
//			for(ky= 0;ky < 2; ky++)
//    			for(kx = 0;kx < 2; kx++)
//				{
//#pragma HLS PIPELINE
//						Yoffset = (y << 1) + ky;
//						Xoffset = (x << 1) + kx;
//
//						int in_index  = (ky << 1) + kx;
//						Output[in_index][y][x] = Input[0][Yoffset][Xoffset];					
//    			}
//}
//
//void intra_pingpong_wrapper(float *Input,float *Weight, float output_buffer[Tm][Tr][Tc],float beta_buffer[MAX_BETA_LENGTH],
//								 float input_buffer0[Tn][OnChipIB_Height][OnChipIB_Width],float input_buffer1[Tn][OnChipIB_Height][OnChipIB_Width],
//								 int InFM_num,int Input_w,int Input_h,int OutFM_num,int Kernel_size,int Kernel_stride,
//								 int TMP_R,int TMP_C,int TMP_M,int m,int TM_MIN,int TR_MIN,int TC_MIN,int TN,int TRow,int TCol,int Padding,
//								 int IHxIW,int KxK,int IFM_numxKxK,int nLoops,bool IsNL,int LayerType,int TM,int TMP_X_next[1],int TX_MIN_next[1],bool pingpongx,bool input_flag,bool process_flag)
//{
//	static float weight_buffer0[Tm][Tn][K][K];
//#pragma HLS ARRAY_PARTITION variable=weight_buffer0 complete dim=1
//#pragma HLS ARRAY_PARTITION variable=weight_buffer0 complete dim=2
//
//	static float weight_buffer1[Tm][Tn][K][K];
//#pragma HLS ARRAY_PARTITION variable=weight_buffer1 complete dim=1
//#pragma HLS ARRAY_PARTITION variable=weight_buffer1 complete dim=2
//
//	static int NOP[1];
//	static int tmp_x;
//	static int tmp_tx_min;
//
//	if(LayerType==0)
//	{
//
//		if(!input_flag)
//			return;
//		TMP_X_next[0] = TMP_M;//consider by the inner-out loop
//		TX_MIN_next[0] = TM_MIN;// like above
//
//		bool pingpong = 0;
//		int TMP_N_next0[1];
//		int TMP_N_next1[1];
//		int n;
//		int TMP_N;
//		for(TMP_N = 0,n = 0;n < nLoops+1; n++,TMP_N += TN)
//		{
//			if(pingpong == 1)
//			{
//				copy_input_weight(Input,Weight,InFM_num,Input_w,Input_h,OutFM_num,Kernel_size,Kernel_stride,TMP_R,TMP_C,TMP_M,TMP_N,
//					TM_MIN,TN,TRow,TCol,Padding,input_buffer1,weight_buffer1,TMP_N_next1,n!=nLoops,1,(m==0)&&(n==0),IHxIW,KxK,IFM_numxKxK,LayerType);
//				compute(input_buffer0,output_buffer,weight_buffer0,beta_buffer,TMP_N_next0,Kernel_size,Kernel_stride,TMP_M,TM_MIN,TR_MIN,TC_MIN,n!=0,IsNL,n==nLoops);
//				pingpong = 0;
//			}else
//			{
//				copy_input_weight(Input,Weight,InFM_num,Input_w,Input_h,OutFM_num,Kernel_size,Kernel_stride,TMP_R,TMP_C,TMP_M,TMP_N,
//					TM_MIN,TN,TRow,TCol,Padding,input_buffer0,weight_buffer0,TMP_N_next0,n!=nLoops,1,(m==0)&&(n==0),IHxIW,KxK,IFM_numxKxK,LayerType);
//				compute(input_buffer1,output_buffer,weight_buffer1,beta_buffer,TMP_N_next1,Kernel_size,Kernel_stride,TMP_M,TM_MIN,TR_MIN,TC_MIN,n!=0,IsNL,n==nLoops);
//				pingpong = 1;
//			}
//		}
//	}
//	else if(LayerType==1)
//	{
//		if(pingpongx==0)
//		{
//			TMP_X_next[0] = tmp_x;
//			TX_MIN_next[0] = tmp_tx_min;
//			tmp_x = TMP_M;
//			tmp_tx_min = TM_MIN;
//
//			copy_input_weight(Input,Weight,InFM_num,Input_w,Input_h,OutFM_num,Kernel_size,Kernel_stride,TMP_R,TMP_C,TMP_M,TMP_M,
//				TM_MIN,TM,TRow,TCol,0,input_buffer0,NULL,NOP,input_flag,0,0,IHxIW,KxK,IFM_numxKxK,LayerType);
//			pool_yolo2(input_buffer1,output_buffer,Kernel_size,Kernel_stride,TX_MIN_next[0],TR_MIN,TC_MIN,process_flag);
//		}else
//		{
//			TMP_X_next[0] = tmp_x;
//			TX_MIN_next[0] = tmp_tx_min;
//			tmp_x = TMP_M;
//			tmp_tx_min = TM_MIN;
//
//			copy_input_weight(Input,Weight,InFM_num,Input_w,Input_h,OutFM_num,Kernel_size,Kernel_stride,TMP_R,TMP_C,TMP_M,TMP_M,
//				TM_MIN,TM,TRow,TCol,0,input_buffer1,NULL,NOP,input_flag,0,0,IHxIW,KxK,IFM_numxKxK,LayerType);
//			pool_yolo2(input_buffer0,output_buffer,Kernel_size,Kernel_stride,TX_MIN_next[0],TR_MIN,TC_MIN,process_flag);
//		}
//
//	}
//	else if(LayerType==2)
//	{
//		if(pingpongx==0)
//		{
//			TMP_X_next[0] = tmp_x;
//			TX_MIN_next[0] = tmp_tx_min;
//			tmp_x = TMP_M;
//			tmp_tx_min = TM_MIN;
//
//			copy_input_weight(Input,Weight,InFM_num,Input_w,Input_h,OutFM_num,Kernel_size,Kernel_stride,TMP_R,TMP_C,TMP_M,TMP_M,
//				TM_MIN,TM,TRow,TCol,0,input_buffer0,NULL,NOP,input_flag,0,0,IHxIW,KxK,IFM_numxKxK,LayerType);
//			reorg_yolo2(input_buffer1,output_buffer,Kernel_size,Kernel_stride,TX_MIN_next[0],TR_MIN,TC_MIN,process_flag);
//		}else
//		{
//			TMP_X_next[0] = tmp_x;
//			TX_MIN_next[0] = tmp_tx_min;
//			tmp_x = TMP_M;
//			tmp_tx_min = TM_MIN;
//
//			copy_input_weight(Input,Weight,InFM_num,Input_w,Input_h,OutFM_num,Kernel_size,Kernel_stride,TMP_R,TMP_C,TMP_M,TMP_M,
//				TM_MIN,TM,TRow,TCol,0,input_buffer1,NULL,NOP,input_flag,0,0,IHxIW,KxK,IFM_numxKxK,LayerType);
//			reorg_yolo2(input_buffer0,output_buffer,Kernel_size,Kernel_stride,TX_MIN_next[0],TR_MIN,TC_MIN,process_flag);
//		}
//
//	}
//
//}
//
//void YOLO2_FPGA(float *Input,float *Output,float *Weight,float *Beta,const int InFM_num,const int OutFM_num,
//							  const int Kernel_size,const int Kernel_stride,
//							  const int Input_w,const int Input_h,const int Padding,const bool IsNL,const bool IsBN,
//							  const int TM,const int TN,const int TR,const int TC,
//							  const int mLoops,const int nLoops,const int rLoops,const int cLoops,const int LayerType)
//{
//	//const int output_w = (Input_w - Kernel_size + 2*Padding)/Kernel_stride + 1 ;
//	//const int output_h = (Input_h - Kernel_size + 2*Padding)/Kernel_stride + 1 ;
//	int output_w = (Input_w - Kernel_size + (Padding << 1))/Kernel_stride + 1 ;
//	int output_h = (Input_h - Kernel_size + (Padding << 1))/Kernel_stride + 1 ;
//	if(LayerType==1)
//	{
//		output_w = (Input_w - 1)/Kernel_stride + 1 ;
//		output_h = (Input_h - 1)/Kernel_stride + 1 ;
//	}
//	const int OHxOW = output_h*output_w;
//	const int TRow = (TR-1)*Kernel_stride+Kernel_size;
//	const int TCol = (TC-1)*Kernel_stride+Kernel_size;
//	const int IHxIW   = Input_h*Input_w;
//	const int KxK = Kernel_size*Kernel_size;
//	const int IFM_numxKxK = InFM_num*KxK;
//	const int mLoops_bound = LayerType ? (mLoops + 2): (mLoops + 1);
//
//	static float input_buffer0[Tn][OnChipIB_Height][OnChipIB_Width];
//#pragma HLS ARRAY_PARTITION variable=input_buffer0 complete dim=1
//
//	static float input_buffer1[Tn][OnChipIB_Height][OnChipIB_Width];
//#pragma HLS ARRAY_PARTITION variable=input_buffer1 complete dim=1
//
//	static float output_buffer[Tm][Tr][Tc];
//#pragma HLS ARRAY_PARTITION variable=output_buffer complete dim=1
//
//	static float output_buffer1[Tm][Tr][Tc];
//#pragma HLS ARRAY_PARTITION variable=output_buffer1 complete dim=1
//
//	static float beta_buffer[MAX_BETA_LENGTH];
//
//	int r,c,m;
///////////////////////////////////param
//	int TMP_R,TMP_C,TMP_M;
//	int TM_MIN,TR_MIN,TC_MIN;
/////////////////////////////////////////
//
//	int TMP_M_next0[1];
//	int TMP_M_next1[1];
//	int TM_MIN_next0[1];
//	int TM_MIN_next1[1];
//	bool pingpongm;
//
//	if(LayerType==0)
//		memcpy(beta_buffer,Beta,OutFM_num*sizeof(float));
//
//	for(TMP_R = 0,r = 0; r < rLoops; r++, TMP_R += TR)
//	{
//		TR_MIN = MIN(TR,output_h -TMP_R);
//		for(TMP_C = 0,c = 0; c < cLoops; c++,TMP_C += TC)
//		{
//			TC_MIN = MIN(TC,output_w -TMP_C);
//			pingpongm = 0;
//			for(TMP_M = 0, m = 0; m < mLoops_bound; m++,TMP_M += TM)
//			{
//				TM_MIN = MIN(TM,OutFM_num-TMP_M);
//				bool MneZero = (m!=0);
//				bool MneOne = (m!=1);
//				bool MnemLoops = (m!=mLoops);
//				bool MneMLoopsaddOne = (m!=(mLoops+1));
//				bool input_flag = LayerType ? MnemLoops&&MneMLoopsaddOne: MnemLoops;
//				bool process_flag = LayerType ? MneZero&&MneMLoopsaddOne : MnemLoops;
//				bool write_flag = LayerType ? MneZero&&MneOne : MneZero;
//
//				if(pingpongm==0)
//				{
//					intra_pingpong_wrapper(Input,Weight,output_buffer1,beta_buffer,input_buffer0,input_buffer1,
//									InFM_num, Input_w, Input_h, OutFM_num, Kernel_size, Kernel_stride,
//									TMP_R, TMP_C, TMP_M, m, TM_MIN, TR_MIN, TC_MIN, TN, TRow, TCol, Padding,IHxIW,KxK,IFM_numxKxK,nLoops,IsNL,LayerType,TM, TMP_M_next1,TM_MIN_next1, pingpongm, input_flag, process_flag);
//
//					write_back_output_reorg(output_buffer,Output,TMP_R,TMP_C,TMP_M_next0[0],output_w,output_h,TM_MIN_next0[0],TR_MIN,TC_MIN,OHxOW,write_flag);
//					pingpongm = 1;
//				}else
//				{
//					intra_pingpong_wrapper(Input,Weight,output_buffer,beta_buffer,input_buffer0,input_buffer1,
//									InFM_num, Input_w, Input_h, OutFM_num, Kernel_size, Kernel_stride,
//									TMP_R, TMP_C, TMP_M, m, TM_MIN, TR_MIN, TC_MIN, TN, TRow, TCol, Padding,IHxIW,KxK,IFM_numxKxK,nLoops,IsNL,LayerType,TM, TMP_M_next0,TM_MIN_next0, pingpongm, input_flag, process_flag);
//
//					write_back_output_reorg(output_buffer1,Output,TMP_R,TMP_C,TMP_M_next1[0],output_w,output_h,TM_MIN_next1[0],TR_MIN,TC_MIN,OHxOW,write_flag);
//					pingpongm = 0;
//				}
//
//			}
//		}
//	}
//}
//
//int Weight_reorgnaization_anti(float *Weight,float *Weight_reorg,float* Alpha,int IFM_NUM,int OFM_NUM,int Kernel_size,int TM,int TN,const bool IsBN)
//{
//	const int KxK = Kernel_size*Kernel_size;
//	const int IFM_NUMxKxK = IFM_NUM*KxK;
//
//	int m,n;
//	int tm,tn,tk;
//
//	float weight_buffer[Tm*Tn*K*K];
//	float weight_buffer2[Tm*Tn*K*K];
//
//	int TM_MIN,TN_MIN;
//	int offset = 0;
//
//	for( m = 0; m < OFM_NUM; m += TM)
//	{
//		TM_MIN = MIN(TM,OFM_NUM - m);
//
//		for(n = 0;n < IFM_NUM; n += TN)
//		{
//			TN_MIN = MIN(TN,IFM_NUM - n);
//
//			int Woffset = m*IFM_NUMxKxK + n*KxK;
//
//			for(tm = 0;tm < TM_MIN; tm++)
//			{
//				memcpy((float *)(weight_buffer + tm*TN_MIN*KxK),
//					(float *)(Weight + tm*IFM_NUMxKxK + Woffset),TN_MIN*KxK*sizeof(float));
//			}
//
//			int TN_MINxTM_MIN = TN_MIN*TM_MIN;
//
//			for(tk = 0;tk < KxK; tk++)
//				for(tm = 0;tm < TM_MIN; tm++)
//					for(tn = 0;tn < TN_MIN;tn++)
//					{
//						weight_buffer2[tk*TN_MINxTM_MIN + tm*TN_MIN + tn] = weight_buffer[tm*TN_MIN*KxK + tn*KxK + tk];
//					}
//
//
//
//			memcpy((float *)(Weight_reorg+offset),weight_buffer2,TM_MIN*TN_MIN*KxK*sizeof(float));
//			offset += TM_MIN*TN_MIN*KxK;
//		}							
//	}
//
//	return 0;
//}
//
//#define REORG_GEN
//
//void yolov2_hls_ps(network *net, float *input)
//{
//	int x;
//
//	network orig = *net;
//	net->input = input;
//
//	int weight_offset[32] = {864, 18432, 73728, 8192, 73728,
//		294912, 32768, 294912, 1179648, 131072, 1179648, 131072,
//		1179648, 4718592, 524288, 4718592, 524288, 4718592, 9437184,
//		9437184, 32768, 11796480, 435200, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//	int beta_offset[32] = {32, 64, 128, 64, 128, 256, 128, 256, 512, 256, 512, 256, 512, 1024,
//		512, 1024, 512, 1024, 1024, 1024, 64, 1024, 425, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//	int offset_index = 0;
//
//	float *Weight_buf = (float *)calloc(203767168/4,sizeof(float));
//	float *Beta_buf   = (float *)calloc(43044/4,sizeof(float));
//
//	//FILE *fp_w = fopen("weightsv2_comb_reorg.bin", "rb");
// //   if(!fp_w) file_error("weightsv2_comb_reorg.bin");
//
//	FILE *fp_w = fopen("weightsv2_comb.bin", "rb");
//    if(!fp_w) file_error("weightsv2_comb.bin");
//
//#ifdef REORG_GEN
//	float *Weight_reorg_buf = (float *)calloc(203767168/4,sizeof(float));
//	FILE *fp_w_reorg = fopen("weightsv2_comb_reorg.bin", "wb");
//    if(!fp_w_reorg) file_error("weightsv2_comb_reorg.bin");
//#endif
//
//	FILE *fp_b = fopen("biasv2_comb.bin", "rb");
//    if(!fp_b) file_error("biasv2_comb.bin");
//
//	fread(Weight_buf, sizeof(float), 203767168/4, fp_w);
//	fread(Beta_buf, sizeof(float), 43044/4, fp_b);
//
//	fclose(fp_w);
//	fclose(fp_b);
//
//
//#define MEM_LEN (416*416*32+208*208*32)
//	float *Memory_buf = (float*)calloc(MEM_LEN+1024+1024,sizeof(float));
//	float *Memory_top = Memory_buf+1024;
//	float *Memory_bottom = Memory_top + MEM_LEN;
//	memcpy(Memory_top,input,416*416*3*sizeof(float));//416x416x3 input_pic
//
//	float* in_ptr[32];
//	float* out_ptr[32];
//
//#define ROUTE16_LEN (26*26*512)
//#define CONV27_LEN (13*13*256)
//#define CONV24_LEN (13*13*1024)
//
//	for(x=0;x<18;x++)
//	{
//		if(x%2==0)
//		{
//			in_ptr[x] = Memory_top;
//			out_ptr[x] = Memory_bottom - net->layers[x].outputs ;
//		}
//		else
//		{
//			in_ptr[x] = out_ptr[x-1];
//			out_ptr[x] = Memory_top;
//		}
//	}
//
//	for(x=18;x<25;x++)
//	{
//		if(x%2==0)
//		{
//			in_ptr[x] = Memory_top;
//			out_ptr[x] = Memory_bottom - ROUTE16_LEN - net->layers[x].outputs;
//		}else
//		{
//			in_ptr[x] = out_ptr[x-1];
//			out_ptr[x] = Memory_top;
//		}
//	}
//
//	in_ptr[26] = Memory_bottom - ROUTE16_LEN;
//	out_ptr[26] = Memory_top;
//
//	in_ptr[27] = Memory_top;
//	out_ptr[27] = Memory_bottom - ROUTE16_LEN - CONV24_LEN - CONV27_LEN;
//
//	in_ptr[29] = out_ptr[27];
//	out_ptr[29] = Memory_top;
//
//	in_ptr[30] = Memory_top;
//	out_ptr[30] = Memory_bottom - net->layers[30].outputs;
//
//	in_ptr[31] = out_ptr[30];
//
//    network netp = *net;
//    int i;
//	int woffset = 0;
//	int aoffset = 0;
//	int boffset = 0;
//	int TR,TC,TM,TN;
//	int output_w,output_h;
//	int rLoops,cLoops,mLoops,nLoops;
//	double sum_gop = 0.0;
//
//    for(i = 0; i < netp.n; ++i)
//	{
//        netp.index = i;
//        layer l = netp.layers[i];
//		printf("Layer[%2d]: ",i);
//		switch(l.type)
//		{
//			case CONVOLUTIONAL:
//				printf("outputMemory:%8d;BN=%d;Activation=%d;conv  %5d %2d x%2d /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d  %5.3f BFLOPs\n",l.outputs,l.batch_normalize,l.activation, l.n, l.size, l.size, l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c, (2.0 * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w)/1000000000.);
//				sum_gop += (2.0 * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w)/1000000000.;
//				output_w = (l.w - l.size + 2*l.pad)/l.stride + 1 ;
//				output_h = (l.h - l.size + 2*l.pad)/l.stride + 1 ;
//
//				TR = MIN(((OnChipIB_Height-l.size)/l.stride+1),Tr);//keep Kernel_stride>=1
//				TR = MIN(output_h,TR);
//				TC = MIN(((OnChipIB_Width-l.size)/l.stride+1),Tc);
//				TC = MIN(output_w,TC);
//				TM = MIN(l.n,Tm);
//				TN = MIN(l.c,Tn);
//
//				rLoops = (int)ceil(((float)output_h)/TR);
//				cLoops = (int)ceil(((float)output_w)/TC);
//				mLoops = (int)ceil(((float)l.n)/TM);
//			    nLoops = (int)ceil(((float)l.c)/TN);
//
//				YOLO2_FPGA(in_ptr[i],out_ptr[i],Weight_buf+woffset,Beta_buf+boffset,
//					l.c,l.n,l.size,
//					l.stride,l.w,l.h,l.pad,l.activation==LEAKY?1:0,l.batch_normalize?1:0,
//					TM,TN,TR,TC,
//					mLoops,nLoops,rLoops,cLoops,0);
//#ifdef REORG_GEN
//				Weight_reorgnaization_anti(Weight_buf + woffset,Weight_reorg_buf + woffset,NULL,l.c,l.n,l.size,TM,TN,0);
//#endif
//				printf("TR=%d,TC=%d,TM=%d,TN=%d,rLoops=%d,cLoops=%d,mLoops=%d,nLoops=%d\n",TR,TC,TM,TN,rLoops,cLoops,mLoops,nLoops);
//
//				woffset += weight_offset[offset_index];
//				boffset += beta_offset[offset_index];
//				offset_index++;
//
//				break;
//			case MAXPOOL:
//				printf("outputMemory:%8d;max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n",l.outputs, l.size, l.size, l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c);
//				//output_w = (l.w - l.size)/l.stride + 1 ;
//				//output_h = (l.h - l.size)/l.stride + 1 ;
//				output_w = l.out_h;
//				output_h = l.out_w;
//
//				TR = MIN(((OnChipIB_Height-l.size)/l.stride+1),Tr);//keep Kernel_stride>=1
//				TC = MIN(((OnChipIB_Width-l.size)/l.stride+1),Tc);
//
//				TR = MIN(output_h,TR);
//				TC = MIN(output_w,TC);
//				TM = MIN(Tm,Tn);
//				TM = MIN(l.c,TM);
//
//				rLoops = (int)ceil(((float)output_h)/TR);
//				cLoops = (int)ceil(((float)output_w)/TC);
//				mLoops = (int)ceil(((float)l.c)/TM);
//
//				YOLO2_FPGA(in_ptr[i],out_ptr[i],NULL,NULL,l.c,l.c,
//					l.size,l.stride,l.w,l.h,l.pad,0,0,TM,0,TR,TC,mLoops,0,rLoops,cLoops,1);
//
//				break;
//			case REORG:
//				printf("outputMemory:%8d;reorg              /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n",l.outputs,  l.stride, l.w, l.h, l.c, l.out_w, l.out_h, l.out_c);			
//				output_w = 26;
//				output_h = 32*13;
//
//				TR = MIN(((OnChipIB_Height-l.stride)/l.stride+1),Tr);//keep Kernel_stride>=1
//				TR = MIN(output_h,TR);
//				TC = MIN(((OnChipIB_Width-l.stride)/l.stride+1),Tc);
//				TC = MIN(output_w,TC);
//				TM = 4;
//
//				rLoops = (int)ceil(((float)output_h)/TR);
//				cLoops = (int)ceil(((float)output_w)/TC);
//				mLoops = 1;
//
//				YOLO2_FPGA(in_ptr[i],out_ptr[i],NULL,NULL,1,4,
//							  l.stride,l.stride,52,32*26,0,0,0,TM,0,TR,TC,mLoops,0,rLoops,cLoops,2);
//
//				break;
//			case ROUTE:
//				printf("outputMemory:%8d;route ",l.outputs);
//				int j;
//				for(j = 0; j < l.n; ++j){
//					printf(" %d", l.input_layers[j]);
//				}
//				printf("\n");
//				break;
//			case REGION:
//				printf("outputMemory:%8d;Detection\n",l.outputs);
//				netp.input = in_ptr[i];
//				forward_region_layer(l,netp);
//				break;
//		}
//
//		netp.input = l.output;
//
//    }
//	printf("SUM_GOP=%g\n",sum_gop);
//	*net = orig;
//
//#ifdef REORG_GEN
//	fwrite(Weight_reorg_buf, sizeof(float), 203767168/4, fp_w_reorg);
//	fclose(fp_w_reorg);
//	free(Weight_reorg_buf);
//#endif
//	free(Memory_buf);
//	free(Weight_buf);
//	free(Beta_buf);
//
//}
/////////////////////////////////////////////////////////////////////////20181229 anti-reorg ok end n4m32


#endif
