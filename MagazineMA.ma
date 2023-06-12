[top]
components : Mag@Magazine

in : in_initBullets
in : in_initMagSeating
in : in_bulletLoaded

out : out_bulletReady

Link : in_initBullets in_initBullets@Mag
Link : in_initMagSeating in_initMagSeating@Mag
Link : in_bulletLoaded in_bulletLoaded@Mag
Link : out_bulletReady@Mag out_bulletReady

[Mag]
preparation : 00:00:00:000
