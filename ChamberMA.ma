[top]
components : Chbr@Chamber

in : in_isDud
in : in_bulletLoaded

out : out_boltBack
out : out_bulletFired
out : out_casing

Link : in_isDud in_isDud@Chbr
Link : in_bulletLoaded in_bulletLoaded@Chbr
Link : out_boltBack@Chbr out_boltBack
Link : out_bulletFired@Chbr out_bulletFired
Link : out_casing@Chbr out_casing

[Chbr]
preparation : 00:00:00:020