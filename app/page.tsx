"use client";
import { useState } from "react";
import ImageModal from "./components/ImageModal";
import { SiGoogledrive } from "react-icons/si";
import { SiMega } from "react-icons/si";



const imagens = [
  "entropia.png",
  "heatmap.png",
  "pacotes_por_janela.png",
  "traffic_time_series.png",
  "ipg_top10_line.png",
  "tam_frequencia.png",
  "tam_medio_geral.png",
  "size_cdf.png",
];

const downloads = [
  "anomalos.cpp",
  "burstiness.cpp",
  "entropia.cpp",
  "entropia.py",
  "gen_total_dist.cpp",
  "heatmap.cpp",
  "heatmap.py",
  "horizontal_scan.cpp",
  "ipg_geral.cpp",
  "ipg_analysis.py",
  "ipg_skew_kurt.cpp",
  "media_ipg.cpp",
  "pacotes_por_janela.cpp",
  "pacotes_por_janela.py",
  "size_cdf.cpp",
  "tam_frequencia.cpp",
  "tam_medio.cpp",
  "tam_medio.py",
  "top10_active.cpp",
  "top10.py",
  "volume_dados.cpp",
];

export default function Home() {
  const [isOpen, setIsOpen] = useState(false);
  const [modalImg, setModalImg] = useState({ src: "", alt: "", descricao: "" });
  const [showBursts, setShowBursts] = useState(false);
  const [showSilences, setShowSilences] = useState(false);
  const [showDest, setShowDest] = useState(false);

  const totalPacotes = 190431954;
  const tamanhoMedio = 66.33;
  const gapsCalculados = 190431953;
  const ipgMedio = 4.73;
  const numJanelas = 901;
  const mediaPorJanela = 211356.22;
  const desvioJanela = 36711.43;
  const burstinessCV = 0.1737;
  const numRajadas = 69;
  const duracaoMediaRajada = 2.23;
  const skewness = 2.8160;
  const kurtosis = 14.3091;
  const mediaDestUnicos = 6.50;
  const desvioDest = 8773.97;
  const thresholdDest = 17554.45;

  const bursts = [
  { time: 1718722986, count: 302943 },
  { time: 1718723112, count: 277142 },
  { time: 1718723113, count: 300273 },
  { time: 1718723114, count: 311900 },
  { time: 1718723115, count: 302687 },
  { time: 1718723116, count: 298817 },
  { time: 1718723117, count: 276638 },
  { time: 1718723118, count: 275423 },
  { time: 1718723119, count: 269087 },
  { time: 1718723120, count: 276492 },
  { time: 1718723131, count: 265947 },
  { time: 1718723132, count: 265380 },
  { time: 1718723135, count: 259598 },
  { time: 1718723136, count: 288609 },
  { time: 1718723137, count: 279291 },
  { time: 1718723138, count: 267580 },
  { time: 1718723139, count: 267160 },
  { time: 1718723140, count: 285926 },
  { time: 1718723141, count: 280857 },
  { time: 1718723151, count: 251005 },
  { time: 1718723152, count: 258282 },
  { time: 1718723155, count: 249433 },
  { time: 1718723160, count: 258330 },
  { time: 1718723166, count: 261787 },
  { time: 1718723183, count: 250319 },
  { time: 1718723184, count: 275695 },
  { time: 1718723185, count: 261141 },
  { time: 1718723187, count: 262615 },
  { time: 1718723188, count: 287745 },
  { time: 1718723189, count: 274120 },
  { time: 1718723190, count: 280054 },
  { time: 1718723191, count: 276711 },
  { time: 1718723193, count: 265633 },
  { time: 1718723195, count: 264847 },
  { time: 1718723196, count: 257435 },
  { time: 1718723199, count: 264389 },
  { time: 1718723200, count: 268079 },
  { time: 1718723204, count: 259936 },
  { time: 1718723205, count: 261313 },
  { time: 1718723209, count: 254956 },
  { time: 1718723211, count: 259839 },
  { time: 1718723212, count: 258387 },
  { time: 1718723213, count: 256527 },
  { time: 1718723215, count: 304959 },
  { time: 1718723216, count: 266111 },
  { time: 1718723223, count: 251613 },
  { time: 1718723224, count: 283906 },
  { time: 1718723225, count: 258430 },
  { time: 1718723226, count: 281736 },
  { time: 1718723227, count: 276039 },
  { time: 1718723228, count: 260135 },
  { time: 1718723229, count: 257099 },
  { time: 1718723231, count: 259388 },
  { time: 1718723232, count: 301617 },
  { time: 1718723233, count: 297005 },
  { time: 1718723234, count: 269850 },
  { time: 1718723235, count: 299694 },
  { time: 1718723236, count: 268704 },
  { time: 1718723238, count: 253487 },
  { time: 1718723239, count: 269342 },
  { time: 1718723240, count: 250698 },
  { time: 1718723245, count: 260862 },
  { time: 1718723247, count: 258076 },
  { time: 1718723248, count: 269952 },
  { time: 1718723251, count: 275092 },
  { time: 1718723252, count: 256849 },
  { time: 1718723253, count: 273447 },
  { time: 1718723254, count: 251374 },
  { time: 1718723255, count: 267338 },
  { time: 1718723257, count: 253416 },
  { time: 1718723259, count: 266618 },
  { time: 1718723264, count: 260982 },
  { time: 1718723267, count: 259920 },
  { time: 1718723268, count: 248448 },
  { time: 1718723271, count: 257353 },
  { time: 1718723272, count: 262416 },
  { time: 1718723288, count: 257481 },
  { time: 1718723312, count: 249632 },
  { time: 1718723323, count: 256068 },
  { time: 1718723328, count: 256110 },
  { time: 1718723329, count: 269462 },
  { time: 1718723330, count: 257253 },
  { time: 1718723331, count: 251819 },
  { time: 1718723332, count: 253103 },
  { time: 1718723339, count: 254590 },
  { time: 1718723340, count: 254806 },
  { time: 1718723363, count: 256098 },
  { time: 1718723367, count: 248564 },
  { time: 1718723379, count: 272533 },
  { time: 1718723380, count: 263868 },
  { time: 1718723381, count: 255293 },
  { time: 1718723382, count: 252062 },
  { time: 1718723384, count: 258546 },
  { time: 1718723385, count: 267409 },
  { time: 1718723388, count: 253932 },
  { time: 1718723389, count: 249792 },
  { time: 1718723404, count: 251630 },
  { time: 1718723407, count: 260034 },
  { time: 1718723412, count: 261392 },
  { time: 1718723426, count: 252576 },
  { time: 1718723431, count: 253695 },
  { time: 1718723437, count: 259601 },
  { time: 1718723440, count: 252602 },
  { time: 1718723456, count: 248280 },
  { time: 1718723459, count: 258879 },
  { time: 1718723460, count: 258651 },
  { time: 1718723462, count: 273599 },
  { time: 1718723464, count: 277230 },
  { time: 1718723465, count: 279651 },
  { time: 1718723466, count: 263819 },
  { time: 1718723467, count: 265162 },
  { time: 1718723468, count: 275275 },
  { time: 1718723469, count: 290620 },
  { time: 1718723470, count: 270054 },
  { time: 1718723471, count: 298808 },
  { time: 1718723472, count: 284358 },
  { time: 1718723473, count: 258732 },
  { time: 1718723480, count: 249774 },
  { time: 1718723496, count: 258998 },
  { time: 1718723498, count: 249340 },
  { time: 1718723499, count: 256145 },
  { time: 1718723501, count: 257103 },
  { time: 1718723502, count: 249900 },
  { time: 1718723503, count: 273143 },
  { time: 1718723504, count: 261727 },
  { time: 1718723508, count: 253886 },
  { time: 1718723523, count: 256414 },
  { time: 1718723526, count: 276811 },
  { time: 1718723528, count: 259869 },
  { time: 1718723529, count: 249013 },
  { time: 1718723536, count: 268505 },
  { time: 1718723540, count: 265342 },
  { time: 1718723541, count: 258510 },
  { time: 1718723557, count: 252718 },
  { time: 1718723563, count: 253921 },
  { time: 1718723564, count: 259517 },
  { time: 1718723571, count: 249604 },
  { time: 1718723572, count: 250728 },
  { time: 1718723573, count: 249438 },
  { time: 1718723581, count: 253057 },
  { time: 1718723582, count: 253801 },
  { time: 1718723583, count: 249068 },
  { time: 1718723584, count: 260770 },
  { time: 1718723585, count: 249222 },
  { time: 1718723587, count: 267344 },
  { time: 1718723588, count: 250150 },
  { time: 1718723599, count: 251146 },
  { time: 1718723607, count: 254754 },
  { time: 1718723611, count: 248665 },
  { time: 1718723612, count: 255850 },
  { time: 1718723621, count: 248846 },
  { time: 1718723623, count: 256439 },
  { time: 1718723624, count: 254217 },
  { time: 1718723625, count: 253579 },
];
  const silences = [
  { start: 'nao consegui captar', end: 'nao consegui captar' },
];
  const destAnom = [
  { ip: '222.180.5.28', count: 24891 },
  { ip: '4.207.94.148', count: 31937 },
  { ip: '18.30.38.101', count: 34854 },
  { ip: '203.77.116.15', count: 21180274 },
  { ip: '52.163.43.40', count: 30764 },
  { ip: '3.237.210.92', count: 31892 },
  { ip: '185.52.116.44', count: 34782 },
  { ip: '3.241.137.39', count: 25390 },
  { ip: '185.24.33.211', count: 25112 },
  { ip: '47.208.237.164', count: 32680 },
  { ip: '173.249.184.67', count: 33778 },
  { ip: '172.206.146.95', count: 32657 },
  { ip: '15.243.154.77', count: 71155 },
  { ip: '13.36.226.13', count: 18279 },
  { ip: '167.172.111.7', count: 61707 },
  { ip: '87.255.153.81', count: 53265 },
  { ip: '185.24.33.252', count: 52478 },
  { ip: '4.153.40.151', count: 18296 },
  { ip: '80.184.112.57', count: 28796 },
  { ip: '206.26.96.97', count: 20445 },
  { ip: '172.206.148.37', count: 32466 },
  { ip: '80.174.5.242', count: 99400 },
  { ip: '18.63.86.38', count: 32678 },
  { ip: '209.56.9.76', count: 30357 },
  { ip: '80.184.112.46', count: 28476 },
  { ip: '45.6.2.126', count: 92278 },
  { ip: '185.24.33.224', count: 65301 },
  { ip: '195.151.248.51', count: 28057 },
  { ip: '79.12.198.113', count: 28633 },
  { ip: '210.234.187.172', count: 37722 },
  { ip: '78.135.14.26', count: 40866 },
  { ip: '4.153.231.103', count: 19748 },
  { ip: '202.230.205.198', count: 25352 },
  { ip: '103.64.216.224', count: 27172 },
  { ip: '3.241.141.0', count: 31121 },
  { ip: '172.180.85.189', count: 33211 },
  { ip: '185.65.127.218', count: 36762 },
  { ip: '18.30.114.51', count: 50297 },
  { ip: '3.120.10.250', count: 41160 },
  { ip: '18.250.113.107', count: 67209 },
  { ip: '61.82.91.114', count: 49439 },
  { ip: '185.85.100.84', count: 19192 },
  { ip: '3.239.14.151', count: 26060 },
  { ip: '3.104.187.188', count: 28986 },
  { ip: '117.166.138.230', count: 40360 },
  { ip: '89.43.81.170', count: 152812 },
  { ip: '80.184.112.47', count: 30582 },
  { ip: '78.135.13.133', count: 32970 },
  { ip: '79.12.195.78', count: 99321 },
  { ip: '185.3.143.215', count: 36836 },
  { ip: '57.110.205.253', count: 29425 },
  { ip: '176.175.175.238', count: 18841 },
  { ip: '80.160.0.247', count: 38312 },
  { ip: '3.113.112.140', count: 32081 },
  { ip: '161.62.41.137', count: 20603 },
  { ip: '141.228.228.15', count: 40265 },
  { ip: '154.202.159.244', count: 22944 },
  { ip: '31.227.29.167', count: 39011 },
  { ip: '4.153.222.78', count: 30983 },
  { ip: '172.246.238.153', count: 19663 },
  { ip: '141.228.228.48', count: 76392 },
  { ip: '79.12.192.29', count: 33055 },
  { ip: '89.43.81.203', count: 60750 },
  { ip: '141.228.228.111', count: 40870 },
  { ip: '103.64.216.229', count: 27326 },
  { ip: '141.228.228.229', count: 44967 },
  { ip: '3.118.16.150', count: 32279 },
  { ip: '141.222.196.101', count: 100308 },
  { ip: '103.64.216.26', count: 86802 },
  { ip: '165.11.177.160', count: 27762 },
  { ip: '18.251.218.138', count: 26033 },
  { ip: '3.115.194.179', count: 31027 },
  { ip: '170.161.227.250', count: 70689 },
  { ip: '167.172.111.110', count: 57137 },
  { ip: '18.24.120.95', count: 73531 },
  { ip: '167.172.97.86', count: 51373 },
  { ip: '78.135.12.249', count: 17731 },
  { ip: '51.144.153.210', count: 42602 },
  { ip: '91.28.49.67', count: 65530 },
  { ip: '87.255.153.65', count: 54129 },
  { ip: '51.145.250.133', count: 359797 },
  { ip: '103.64.216.228', count: 27341 },
  { ip: '172.246.238.112', count: 19669 },
  { ip: '203.77.109.165', count: 25106 },
  { ip: '80.182.11.180', count: 140849 },
  { ip: '18.27.191.250', count: 25314 },
  { ip: '89.43.81.195', count: 55777 },
  { ip: '89.43.85.29', count: 143589 },
  { ip: '172.246.238.98', count: 19524 },
  { ip: '185.24.33.205', count: 65533 },
  { ip: '18.248.219.189', count: 41098 },
  { ip: '79.16.56.109', count: 41344 },
  { ip: '79.16.56.161', count: 43626 },
  { ip: '87.105.37.228', count: 34234 },
  { ip: '5.201.209.254', count: 43490 },
  { ip: '3.239.114.96', count: 31070 },
  { ip: '18.67.91.75', count: 73155 },
  { ip: '51.144.150.245', count: 17638 },
  { ip: '79.16.56.140', count: 57034 },
  { ip: '103.64.216.225', count: 27128 },
  { ip: '18.27.114.84', count: 33013 },
  { ip: '91.28.48.53', count: 17576 },
];

  return (
    <main className="min-h-screen bg-[#111827] text-gray-100 flex flex-col items-center px-6 py-12 font-sans">
      <div className="w-full max-w-5xl space-y-12">

        <section className="mb-12 bg-[#1f2937] p-8 rounded-lg ring-1 ring-gray-700">
          <h2 className="text-3xl font-semibold text-white mb-4">
            Visão Geral do Workflow
          </h2>
          <p className="text-gray-300 leading-relaxed">
            Todo o processamento partiu de capturas de pacotes TCP em C++, que geraram arquivos CSV para cada métrica.
            Em seguida, utilizei <strong>Pandas</strong> e <strong>Matplotlib</strong> em Python para interpretar esses CSVs e produzir todos os gráficos apresentados nesta página.
            Para métricas que não exigiam visualização gráfica, coletei os resultados diretamente no terminal.
          </p>
        </section>


        <section className="bg-[#1f2937] p-6 rounded-lg ring-1 ring-gray-700">
          <h1 className="text-4xl font-bold text-white text-center mb-4">Análise Completa de Tráfego TCP</h1>
          <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-4 gap-4 text-center">
            <div>
              <p className="text-gray-400">Pacotes processados</p>
              <p className="text-white font-semibold">{totalPacotes.toLocaleString()}</p>
            </div>
            <div>
              <p className="text-gray-400">Tamanho médio (bytes)</p>
              <p className="text-white font-semibold">{tamanhoMedio}</p>
            </div>
            <div>
              <p className="text-gray-400">IPG médio (µs)</p>
              <p className="text-white font-semibold">{ipgMedio}</p>
            </div>
            <div>
              <p className="text-gray-400">Gap counts</p>
              <p className="text-white font-semibold">{gapsCalculados.toLocaleString()}</p>
            </div>
            <div>
              <p className="text-gray-400">Janelas</p>
              <p className="text-white font-semibold">{numJanelas}</p>
            </div>
            <div>
              <p className="text-gray-400">Média pkts/janela</p>
              <p className="text-white font-semibold">{mediaPorJanela}</p>
            </div>
            <div>
              <p className="text-gray-400">Burstiness (CV)</p>
              <p className="text-white font-semibold">{burstinessCV}</p>
            </div>
            <div>
              <p className="text-gray-400">Nº rajadas</p>
              <p className="text-white font-semibold">{numRajadas}</p>
            </div>
            <div>
              <p className="text-gray-400">Skewness</p>
              <p className="text-white font-semibold">{skewness}</p>
            </div>
            <div>
              <p className="text-gray-400">Kurtosis</p>
              <p className="text-white font-semibold">{kurtosis}</p>
            </div>
            <div>
              <p className="text-gray-400">Média destinos únicos</p>
              <p className="text-white font-semibold">{mediaDestUnicos}</p>
            </div>
            <div>
              <p className="text-gray-400">Threshold destinos</p>
              <p className="text-white font-semibold">{thresholdDest}</p>
            </div>
          </div>
        </section>

        <section className="space-y-4">
          <h2 className="text-3xl font-semibold border-b border-gray-600 pb-2">Anomalias Temporais</h2>
          <div className="bg-[#1f2937] p-4 rounded-lg ring-1 ring-gray-700">
            <button onClick={() => setShowBursts(!showBursts)} className="w-full text-left flex justify-between items-center text-white font-medium mb-2">
              <span>Bursts Identificados ({bursts.length})</span>
              <span className="text-xl">{showBursts ? '−' : '+'}</span>
            </button>
            {showBursts && (
              <div className="max-h-64 overflow-auto text-sm text-gray-200">
                <table className="w-full table-auto border-collapse">
                  <thead>
                    <tr className="border-b border-gray-600">
                      <th className="py-1 text-left">Início (s)</th>
                      <th className="py-1 text-left">Contagem</th>
                    </tr>
                  </thead>
                  <tbody>
                    {bursts.map((b, idx) => (
                      <tr key={idx} className={idx % 2 === 0 ? 'bg-[#2a2f3a]' : ''}>
                        <td className="py-1">{b.time}</td>
                        <td className="py-1">{b.count.toLocaleString()}</td>
                      </tr>
                    ))}
                  </tbody>
                </table>
              </div>
            )}

            <button onClick={() => setShowSilences(!showSilences)} className="w-full text-left flex justify-between items-center text-white font-medium mt-4 mb-2">
              <span>Silêncios Longos (≥5s)</span>
              <span className="text-xl">{showSilences ? '−' : '+'}</span>
            </button>
            {showSilences && (
              <div className="max-h-32 overflow-auto text-sm text-gray-200">
                {silences.map((s, idx) => (
                  <p key={idx} className="py-1">Silêncio de {s.start}s até {s.end}s</p>
                ))}
              </div>
            )}

            <button onClick={() => setShowDest(!showDest)} className="w-full text-left flex justify-between items-center text-white font-medium mt-4 mb-2">
              <span>IPs com destinos desproporcionais ({destAnom.length})</span>
              <span className="text-xl">{showDest ? '−' : '+'}</span>
            </button>
            {showDest && (
              <div className="max-h-64 overflow-auto text-sm text-gray-200">
                <table className="w-full table-auto border-collapse">
                  <thead>
                    <tr className="border-b border-gray-600">
                      <th className="py-1 text-left">IP</th>
                      <th className="py-1 text-left">Contagem</th>
                    </tr>
                  </thead>
                  <tbody>
                    {destAnom.map((d, idx) => (
                      <tr key={idx} className={idx % 2 === 0 ? 'bg-[#2a2f3a]' : ''}>
                        <td className="py-1">{d.ip}</td>
                        <td className="py-1">{d.count.toLocaleString()}</td>
                      </tr>
                    ))}
                  </tbody>
                </table>
              </div>
            )}
          </div>
        </section>

        <section className="space-y-6">
          <h2 className="text-3xl font-semibold border-b border-gray-600 pb-2">Downloads</h2>

          <p className="text-gray-400">
            Abaixo estão todos os códigos utilizados na extração e análise das métricas. Clique para fazer download:
          </p>

          <a
            href="https://mega.nz/file/5FI2nBQQ#PLUj3MESFKn3_4_0CaRXe9jnUwzXr1ryXhi9ti17lF4"
            target="_blank"
            rel="noopener noreferrer"
            className="flex items-center justify-center gap-2 px-6 py-4 mb-6 bg-red-800 hover:bg-red-700 transition text-white text-lg font-semibold rounded-lg w-full sm:w-auto"
          >
            <img src="/mega.png" alt="Mega" className="w-6 h-6" />
            Ver PCAP utilizado
          </a>

          <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
            {downloads.map((file, idx) => (
              <a
                key={idx}
                href={`/downloads/${file}`}
                download
                className="block px-4 py-2 bg-[#1f2937] rounded-lg text-gray-200 hover:bg-gray-700 transition truncate flex items-center gap-2"
              >
                <SiGoogledrive className="text-[#34A853]" />
                {file}
              </a>
            ))}
          </div>
        </section>
      </div>
    </main>
  );
}

