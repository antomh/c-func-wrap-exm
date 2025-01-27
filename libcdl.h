#ifndef LIBCDL_H
#define LIBCDL_H

/* The MODE argument to `dlopen' contains one of the following: */
#define RTLD_LAZY	0x00001	/* Lazy function call binding.  */
#define RTLD_NOW	0x00002	/* Immediate function call binding.  */
#define	RTLD_BINDING_MASK   0x3	/* Mask of binding time value.  */
#define RTLD_NOLOAD	0x00004	/* Do not load the object.  */
#define RTLD_DEEPBIND	0x00008	/* Use deep binding.  */

# define RTLD_NEXT	    ((void *) -1l)
# define RTLD_DEFAULT	((void *) 0)


extern void *dlopen(const char *filename, int flags);


#endif // LIBCDL_H