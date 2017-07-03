<?php

use Illuminate\Http\Response;
use Illuminate\Http\JsonResponse;
use Lumen\Http\ResponseFactory;

class ResponseFactoryTest extends PHPUnit_Framework_TestCase
{
    public function testMakeDefaultResponse()
    {
        $content = 'hello';
        $responseFactory = new ResponseFactory();
        $response = $responseFactory->make($content);
        $this->assertInstanceOf('\Symfony\Component\HttpFoundation\Response', $response);
        $this->assertEquals($content, $response->getContent());
        $this->assertEquals(Response::HTTP_OK, $response->getStatusCode());
    }

    public function testJsonDefaultResponse()
    {
        $content = ['hello' => 'world'];
        $responseFactory = new ResponseFactory();
        $response = $responseFactory->json($content);

        $this->assertInstanceOf('\Symfony\Component\HttpFoundation\Response', $response);
        $this->assertEquals('{"hello":"world"}', $response->getContent());
        $this->assertEquals(Response::HTTP_OK, $response->getStatusCode());
    }
}
