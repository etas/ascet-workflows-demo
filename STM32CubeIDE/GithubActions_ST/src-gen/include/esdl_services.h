#ifndef ESDL_SERVICES_H_
#define ESDL_SERVICES_H_

/* if esdl_protected_division is already defined, assume the user has provided an own implementation */
#ifndef esdl_protected_division
	/* the macro esdl_protected_division customizes the behavior in case of division by zero */
	#if ESDL_LOGGING_ENABLED
		void asdWriteUserError(char *s, ...);
		#define esdl_protected_division(value, min, max)								\
			(asdWriteUserError("division by zero in %s line %d\n", __FILE__, __LINE__), \
			(((value) < 0) ? min : max))
	#else
		#define esdl_protected_division(value, min, max) (((value) < 0) ? min : max)
	#endif
#endif

#endif /* ESDL_SERVICES_H_ */
