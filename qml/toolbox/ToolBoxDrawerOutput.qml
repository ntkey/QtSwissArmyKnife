import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import SAK.Custom
import "../common"

ScrollView {
    id: root

    property alias dataPreprocessor: dataPreprocessorGroupBox
    property alias storer: storerGroupBox.storer

    property alias showWrap: dataPreprocessorGroupBox.showWrap
    property alias showDate: dataPreprocessorGroupBox.showDate
    property alias showTime: dataPreprocessorGroupBox.showTime
    property alias showMs: dataPreprocessorGroupBox.showMs
    property alias showTx: dataPreprocessorGroupBox.showTx
    property alias showRx: dataPreprocessorGroupBox.showRx

    ColumnLayout {
        width: root.width
        ToolBoxDrawerOutputPreprocessor {
            id: dataPreprocessorGroupBox
            Layout.fillWidth: true
            visible: false
        }
        ToolBoxDrawerOutputStorer {
            id: storerGroupBox
            Layout.fillWidth: true
        }
        ToolBoxDrawerOutputHighlighter {
            id: highlighterGroupBox
            Layout.fillWidth: true
        }
    }

    function setDocument(doc) {
        highlighterGroupBox.setDocument(doc)
    }
}
