[top]
components : TA@TrigAssy

in : in_triggerPressed
in : in_firingSelector
in : in_boltBack

out : out_releaseBolt

Link : in_triggerPressed in_triggerPressed@TA
Link : in_firingSelector in_firingSelector@TA
Link : in_boltBack in_boltBack@TA
Link : out_releaseBolt@TA out_releaseBolt

[TA]
preparation : 00:00:00:050