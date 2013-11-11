###############################################################################
# String Stable
###############################################################################
# String stable for 10 vehicles not in network
#./CarFollow_Git --model=3 --veh-cnt=10 --sim-time=100 --conn-pat=2 --pat-cnt=10 --stat-cnt=1 --react-time=0.3 --tau-time=0.1 --update-time=0.1 --nwDelta-time=0.1 --init-hdway-time=1.0 --stable-hdway-time=1.5 --perturb-start-time=20 dummy

# String stable for 100 vehicles not in network
#./CarFollow_Git --model=3 --veh-cnt=100 --sim-time=300 --conn-pat=2 --pat-cnt=100 --stat-cnt=10 --react-time=0.3 --tau-time=0.1 --update-time=0.1 --nwDelta-time=0.1 --init-hdway-time=0.8 --stable-hdway-time=1.5 --perturb-start-time=50 dummy

###############################################################################
# String Unstable, NO Network
###############################################################################
# String unstable for 10 vehicles not in network
#./CarFollow_Git --model=3 --veh-cnt=10 --sim-time=400 --conn-pat=2 --pat-cnt=10 --stat-cnt=1 --react-time=0.5 --tau-time=0.1 --update-time=0.1 --nwDelta-time=0.1 --init-hdway-time=1.0 --stable-hdway-time=1.5 --perturb-start-time=160 dummy

# String unstable for 20 vehicles not in network
#./CarFollow_Git --model=3 --veh-cnt=20 --sim-time=600 --conn-pat=2 --pat-cnt=20 --stat-cnt=2 --react-time=0.5 --tau-time=0.1 --update-time=0.1 --nwDelta-time=0.1 --init-hdway-time=1.0 --stable-hdway-time=1.5 --perturb-start-time=300 dummy

# String unstable for 100 vehicles not in network
#./CarFollow_Git --model=3 --veh-cnt=100 --sim-time=600 --conn-pat=2 --pat-cnt=100 --stat-cnt=5 --react-time=0.5 --tau-time=0.1 --update-time=0.1 --nwDelta-time=0.1 --init-hdway-time=2.0 --stable-hdway-time=2.0 --perturb-start-time=50 dummy

###############################################################################
# String Unstable, WITH Network
###############################################################################
# 100 vehicles, no network
#./CarFollow_Git --model=3 --veh-cnt=100 --sim-time=500 --conn-pat=2 --pat-cnt=100 --stat-cnt=10 --react-time=0.7 --tau-time=0.1 --update-time=0.1 --nwDelta-time=0.1 --init-hdway-time=4.5 --adj-hdway-time=1.0 --perturb-start-time=50 dummy

# 100 vehicles with network
./CarFollow_Git --model=3 --veh-cnt=100 --sim-time=500 --conn-pat=1 --pat-cnt=100 --stat-cnt=10 --react-time=0.7 --tau-time=0.1 --update-time=0.1 --nwDelta-time=0.1 --init-hdway-time=2.0 --adj-hdway-time=1.0 --perturb-start-time=50 dummy

#./CarFollow_Git --model=3 --veh-cnt=100 --sim-time=500 --conn-pat=1 --pat-cnt=100 --stat-cnt=10 --react-time=0.7 --tau-time=0.1 --update-time=0.1 --nwDelta-time=0.1 --init-hdway-time=4.0 --adj-hdway-time=2.0 --perturb-start-time=50 dummy

