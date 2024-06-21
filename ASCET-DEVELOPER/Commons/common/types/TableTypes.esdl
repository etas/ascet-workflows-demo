package common.types;

type T_AXIS_X_REAL is axis real;
type T_AXIS_Y_REAL is axis real;

type T_1D_REAL is table real -> real;
type T_2D_REAL is table real, real -> real;

type T_1D_FIXED_REAL is fixed table real -> real;
type T_2D_FIXED_REAL is fixed table real, real -> real;
type T_1D_GRP_REAL is group table T_AXIS_X_REAL -> real;
type T_2D_GRP_REAL is group table T_AXIS_X_REAL, T_AXIS_Y_REAL -> real;

type T_AXIS_X_INT is axis integer;
type T_AXIS_Y_INT is axis integer;

type T_1D_INT is table integer -> integer;
type T_2D_INT is table integer, integer -> integer;

type T_1D_FIXED_INT is fixed table integer -> integer;
type T_2D_FIXED_INT is fixed table integer, integer -> integer;
type T_1D_GRP_INT is group table T_AXIS_X_INT -> integer;
type T_2D_GRP_INT is group table T_AXIS_X_INT, T_AXIS_Y_INT -> integer;

