import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: hMCmnemo.width
    height: hMCmnemo.height
    Image {
        z: 0
        id: hMCmnemo
        source: "background/mnemoscheme.png"
        // fillMode: Image.PreserveAspectFit
        width: 1070
        height: 900
        fillMode: Image.PreserveAspectCrop
        smooth: true
    }

    ValveButton {
        z: 1
        id: valveButton
        x: 823
        y: 315
    }
    ValveButton {
        z: 1
        id: valveButton1
        x: 206
        y: 507
    }
    Reactor{
        z: 1
        x: 206
        y: 144
    }
    Reactor {
        z: 1
        x: 582
        y: 667
    }
    SensorWidget {
        z: 1
        id: pressureUpstream
        x: 716
        y: 144
    }
    SensorWidget {
        z: 1
        id: pressureDownstream
        x: 277
        y: 667
    }
    TempWidget {
        id: temperatureUpstream
        x: 530
        y: 162
    }
    TempWidget {
        id: temperatureDownstream
        x: 395
        y: 683
    }

    FlowMeterWidget {
        id: flowMeterUpstream
        x: 332
        y: 302
    }

    FlowMeterWidget {
        id: flowMeterDownstream
        x: 530
        y: 494
    }
}

/*##^##
Designer {
    D{i:0}D{i:1;locked:true}D{i:9}D{i:11}
}
##^##*/
