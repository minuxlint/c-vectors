extern void *malloc(size_t );
extern void free(void * );
extern void *memcpy(void *, const void *, size_t );

typedef struct {
	unsigned int data_size;
	size_t size;
	size_t last_element;
} vector_info;

typedef void 	* vector;
typedef int 	* vector_int;
typedef char 	* vector_char;
typedef float 	* vector_float;
typedef double 	* vector_double;

vector vector_Create(unsigned int data_size, size_t size) {
	vector_info* v_info;
	void *m = malloc(sizeof(vector_info) + size*data_size);
	
	v_info = m;
	v_info->data_size = data_size;
	v_info->size = size;
	v_info->last_element = size;

	return m + sizeof(vector_info);
}

void vector_PushBack(void *vector_ptr, void *data_ptr) {
	vector_info *v_info, *new_v_info;
	vector *v = vector_ptr;
	size_t new_size;
	void *m;

	v_info = *v - sizeof(vector_info);

	if (v_info->size == v_info->last_element) {
		new_size = 2*v_info->size + 1;
		m = malloc(sizeof(vector_info) + new_size*(v_info->data_size));
		new_v_info = m;

		new_v_info->data_size = v_info->data_size;
		new_v_info->size = new_size;
		new_v_info->last_element = v_info->last_element;
		
		memcpy(m + sizeof(vector_info), *v, (v_info->data_size) * (v_info->size));

		free(*v - sizeof(vector_info));
		*v = m + sizeof(vector_info);
		v_info = new_v_info;
	}
	
	memcpy(*v + (v_info->last_element)*(v_info->data_size), data_ptr, v_info->data_size);
	v_info->last_element++;
	return;
}

void *vector_PopBack(void *vector_ptr) {
	vector_info *v_info;
	vector *v = vector_ptr;
	
	v_info = *v - sizeof(vector_info);

	v_info->last_element--;
	return *v + (v_info->data_size)*(v_info->last_element);
}

size_t vector_Size(void *vector_ptr) {
	vector_info *v_info;
	vector *v = vector_ptr;

	v_info = *v - sizeof(vector_info);
	return v_info->last_element;
}

void vector_Destroy(void *vector_ptr) {
	vector *v = vector_ptr;

	free(*v - sizeof(vector_info));
	return;
}
