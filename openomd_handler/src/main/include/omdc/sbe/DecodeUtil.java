/*
 * Copyright (C) 2021 javalover123
 * All Rights Reserved.
 */

package omdc.sbe;

import static omdc.sbe.PkgMsgHeaderDecoder.BLOCK_LENGTH;

import java.time.Instant;
import omdc.sbe.PkgMsgHeaderDecoder;
import org.agrona.DirectBuffer;
import org.agrona.sbe.MessageDecoderFlyweight;

/**
 * OMD-C解析工具类
 *
 * @author javalover123
 * @date 2021/8/2
 */
public class DecodeUtil {

    private static final long MAX_MILLISECONDS = 9999999999L;

    public static Instant toInstant(long milliseconds) {
        if (milliseconds > MAX_MILLISECONDS) {
            milliseconds = milliseconds / 1000000;
        }
        return Instant.ofEpochMilli(milliseconds);
    }

    public static <T extends MessageDecoderFlyweight> PkgMsgHeaderDecoder wrapAndApplyHeader(
            final DirectBuffer buffer,
            final int offset,
            final T decoder)
    {
        PkgMsgHeaderDecoder headerDecoder = new PkgMsgHeaderDecoder();
        headerDecoder.wrap(buffer, offset, BLOCK_LENGTH, PkgMsgHeaderDecoder.SCHEMA_VERSION);

        final int templateId = headerDecoder.msgType();
        if (decoder.sbeTemplateId() != templateId)
        {
            throw new IllegalStateException("Invalid TEMPLATE_ID: " + templateId);
        }

        decoder.wrap(
                buffer,
                offset + BLOCK_LENGTH,
                decoder.sbeBlockLength(),
                decoder.sbeSchemaVersion());
        return headerDecoder;
    }

}
