[top]
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