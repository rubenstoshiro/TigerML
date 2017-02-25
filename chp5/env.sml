signature ENV =
sig
	type access
	type ty

	datatype eventry = VarEntry of {ty: ty}
	val base_tenv : ty Symbol.table
	val base_venv : enventry Symbol.table
end

structure Env :> ENV = 
struct
end