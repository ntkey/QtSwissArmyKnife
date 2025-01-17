import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import SAK.Custom
import "../common"

SAKGroupBox {
    id: maskerGroupBox
    title: qsTr("Masker")
    padding: 8

    property SAKMaskerTool rxMasker: null
    property SAKMaskerTool txMasker: null

    QtObject {
        id: settingKeys
        readonly property string maskerRxEnable: "maskerRxEnable"
        readonly property string maskerRxMask: "maskerRxMask"
        readonly property string maskerTxEnable: "maskerTxEnable"
        readonly property string maskerTxMask: "maskerTxMask"
    }

    SAKHexRegularExpressionValidator{ id:hexREV }

    GridLayout {
        columns: 2
        anchors.fill: parent

        SAKCheckBox {
            id: rxMaskerCheckBox
            text: qsTr("Enable reading masker")
            settingKey: settingKeys.maskerRxEnable
            Layout.columnSpan: 2
            onClicked: setMaskerEnable(rxMaskerCheckBox.checked, rxMasker)
            Component.onCompleted: setMaskerEnable(rxMaskerCheckBox.checked, rxMasker)
        }

        SAKCheckBox {
            id: txMaskerCheckBox
            text: qsTr("Enable writing masker")
            settingKey: settingKeys.maskerTxEnable
            Layout.columnSpan: 2
            onClicked: setMaskerEnable(txMaskerCheckBox.checked, txMasker)
            Component.onCompleted: setMaskerEnable(txMaskerCheckBox.checked, txMasker)
        }

        SAKLabel {
            text: qsTr("Reading mask")
        }

        SAKTextField {
            id: rxMaskerField
            validator: hexREV
            maximumLength: 2
            settingKey: settingKeys.maskerRxMask
            Layout.fillWidth: true
            onTextEdited: setMaskerMask(rxMaskerField.text, rxMasker)
            Component.onCompleted: setMaskerMask(rxMaskerField.text, rxMasker)
        }

        SAKLabel {
            text: qsTr("Writing mask")
        }
        SAKTextField {
            id: txMaskerField
            validator: hexREV
            maximumLength: 2
            settingKey: settingKeys.maskerTxMask
            Layout.fillWidth: true
            onTextEdited: setMaskerMask(txMaskerField.text, txMasker)
            Component.onCompleted: setMaskerMask(txMaskerField.text, txMasker)
        }
    }

    function setMaskerEnable(enable, masker) {
        if (masker) {
            masker.enable = enable
        }
    }

    function setMaskerMask(mask, masker) {
        if (masker) {
            var cookedMask = parseInt(mask, 16)
            masker.setMaskCode(cookedMask)
        }
    }
}
