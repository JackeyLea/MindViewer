// DialBackground.qml

import QtQuick 2.15

Item {
    id: carItem
    width: 100
    height: 100

    // 背景圆弧线宽
    property int btm_lineWidth: 15
    // 背景圆弧颜色
    property color btm_backgroundColor: Qt.rgba(0, 0, 0, 0.1);
    // 背景圆弧半径 开始角度 结束角度
    property int btm_r: 20
    property double btm_startAngle: 0
    property double btm_endAngle: 90

    onBtm_lineWidthChanged: canvas.requestPaint()
    onBtm_backgroundColorChanged: canvas.requestPaint()
    onBtm_rChanged: canvas.requestPaint()
    onBtm_startAngleChanged: canvas.requestPaint()
    onBtm_endAngleChanged: canvas.requestPaint()

    // 顶层圆弧线宽
    property int top_lineWidth: 10
    // 顶层圆弧颜色
    property color top_backgroundColor: "lightgreen"
    // 顶层圆弧半径 开始角度 结束角度
    property int top_r: 20
    property double top_startAngle: 0
    property double top_endAngle: 90

    onTop_lineWidthChanged: canvas.requestPaint()
    onTop_backgroundColorChanged: canvas.requestPaint()
    onTop_rChanged: canvas.requestPaint()
    onTop_startAngleChanged: canvas.requestPaint()
    onTop_endAngleChanged: canvas.requestPaint()

    // 刻度盘
    property color dial_color: "#000000"
    property int dial_lineWidth: 3
    property int dial_addR: 2          // 通过调整该变量可以控制刻度盘圆弧与底层圆弧的距离
    property int dial_longNum: 5       // 刻度盘长刻度线的数量
    property int dial_longLen: 10      // 刻度盘长刻度线的长度

    onDial_colorChanged: canvas.requestPaint()
    onDial_lineWidthChanged: canvas.requestPaint()
    onDial_addRChanged: canvas.requestPaint()
    onDial_longNumChanged: canvas.requestPaint()
    onDial_longLenChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        width: carItem.width
        height: carItem.height

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            // 画背景圆弧
            ctx.lineWidth = carItem.btm_lineWidth;
            ctx.strokeStyle = carItem.btm_backgroundColor;
            ctx.beginPath();
            ctx.arc(carItem.width/2, carItem.width/2, carItem.btm_r, (carItem.btm_startAngle/180*Math.PI), (carItem.btm_endAngle/180*Math.PI));
            ctx.stroke();

            // 画大刻度盘
            ctx.lineWidth = carItem.dial_lineWidth;
            ctx.strokeStyle = carItem.dial_color;
            ctx.beginPath();
            ctx.arc(carItem.width/2, carItem.width/2, carItem.btm_r+carItem.btm_lineWidth+carItem.dial_addR, (carItem.btm_startAngle/180*Math.PI), (carItem.btm_endAngle/180*Math.PI));
            var tmp_step = (carItem.btm_endAngle-carItem.btm_startAngle)/carItem.dial_longNum;
            for(var i=carItem.btm_startAngle;i<carItem.btm_endAngle+tmp_step;i+=tmp_step) {
                var tmp_x = (carItem.width/2)+(carItem.btm_r+carItem.btm_lineWidth+carItem.dial_addR)*Math.cos(i/180*Math.PI);
                var tmp_y = (carItem.width/2)+(carItem.btm_r+carItem.btm_lineWidth+carItem.dial_addR)*Math.sin(i/180*Math.PI);
                ctx.moveTo(tmp_x, tmp_y);
                // 绘制长刻度线
                ctx.lineTo(tmp_x+carItem.dial_longLen*Math.cos(i/180*Math.PI), tmp_y+(carItem.dial_longLen*Math.sin(i/180*Math.PI)));
            }
            ctx.stroke();

            // 画顶层圆弧
            ctx.lineWidth = carItem.top_lineWidth;
            ctx.strokeStyle = carItem.top_backgroundColor;
            ctx.beginPath();
            ctx.arc(carItem.width/2, carItem.width/2, carItem.top_r, (carItem.top_startAngle/180*Math.PI), (carItem.top_endAngle/180*Math.PI));
            ctx.stroke();
        }
    }
}
