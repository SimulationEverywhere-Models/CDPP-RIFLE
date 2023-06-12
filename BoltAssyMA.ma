[top]

components : BA@BoltAssy

in : in_bulletReady
in : in_releaseBolt
in : in_boltBack

out : out_boltPosn
out : out_bulletLoaded

Link : in_bulletReady in_bulletReady@BA
Link : in_releaseBolt in_releaseBolt@BA
Link : in_boltBack in_boltBack@BA

Link : out_boltPosn@BA out_boltPosn
Link : out_bulletLoaded@BA out_bulletLoaded

[BA]
preparation : 00:00:00:020