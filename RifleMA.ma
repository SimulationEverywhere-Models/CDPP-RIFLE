[top]
components : MagAssy TA@TrigAssy BA@BoltAssy Chbr@Chamber

in : inInitBullets
in : inInitMagSeating
in : inHandlePosn
in : inTriggerPressed
in : inFiringSelector

out : outBulletFired
out : outCasing
out : outBoltPosn

Link : inInitBullets in_initBullets@MagAssy
Link : inInitMagSeating in_initMagSeating@MagAssy
Link : inHandlePosn in_boltBack@BA
Link : inTriggerPressed in_triggerPressed@TA
Link : inFiringSelector in_firingSelector@TA

Link : out_bulletReady@MagAssy in_bulletReady@BA
Link : out_isDud@MagAssy in_isDud@Chbr
Link : out_releaseBolt@TA in_releaseBolt@BA
Link : out_bulletLoaded@BA in_bulletLoaded@Chbr
Link : out_bulletLoaded@BA in_bulletLoaded@MagAssy
Link : out_boltBack@Chbr in_boltBack@BA
Link : out_boltBack@Chbr in_boltBack@TA

Link : out_bulletFired@Chbr outBulletFired
Link : out_casing@Chbr outCasing
Link : out_boltPosn@BA outBoltPosn

[TA]
preparation : 00:00:00:010

[BA]
preparation : 00:00:00:050

[Chbr]
preparation : 00:00:00:020


[MagAssy]
components : Mag@Magazine Bull@Bullet

in : in_initBullets
in : in_initMagSeating
in : in_bulletLoaded

out : out_bulletReady
out : out_isDud

Link : in_initBullets in_initBullets@Mag
Link : in_initMagSeating in_initMagSeating@Mag
Link : in_bulletLoaded in_bulletLoaded@Mag

Link : out_bulletReady@Mag in_bulletReady@Bull
Link : out_isDud@Bull out_isDud
Link : out_bulletReady@Bull out_bulletReady

[Mag]
preparation : 00:00:00:000

[Bull]
preparation : 00:00:00:000