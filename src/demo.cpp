// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <librsvg/rsvg.h>

#include "demo.h"

#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QDebug>

DDEMO_BEGIN_NAMESPACE
Demo::Demo(QObject *parent) : QObject(parent) {}

Demo::~Demo() {}

int Demo::add(const int a, const int b) { return a + b; }

bool Demo::svg2png(const QString &svgfile, const QString &pngfile,  QSize size)
{
    QImage outPutimage(size, QImage::Format_ARGB32);
    outPutimage.fill(Qt::transparent);
    QPainter outputPainter(&outPutimage);

    // librsvg
    {
        GError *error = nullptr;
        RsvgHandle *handle = rsvg_handle_new_from_file(svgfile.toUtf8().data(), &error);
        if (error) {
            qWarning("DSvgRenderer::load: %s", error->message);
            g_error_free(error);
            return false;
        }

        RsvgDimensionData rsvg_data;

        rsvg_handle_get_dimensions(handle, &rsvg_data);

        QSizeF defaultSize(rsvg_data.width, rsvg_data.height);
        QRectF viewBox(QPointF(0, 0), defaultSize);

        cairo_surface_t *surface = cairo_image_surface_create_for_data(
                    outPutimage.bits(), CAIRO_FORMAT_ARGB32,
                    outPutimage.width(), outPutimage.height(), outPutimage.bytesPerLine());
        cairo_t *cairo = cairo_create(surface);
        cairo_scale(cairo, outPutimage.width() / viewBox.width(), outPutimage.height() / viewBox.height());
        cairo_translate(cairo, -viewBox.x(), -viewBox.y());
        rsvg_handle_render_cairo(handle, cairo);

        cairo_destroy(cairo);
        cairo_surface_destroy(surface);
        g_object_unref(handle);
    }

    return outPutimage.save(pngfile);
}

DDEMO_END_NAMESPACE
